/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:20:27 by aurban            #+#    #+#             */
/*   Updated: 2024/03/05 10:29:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_collision	*new_collision(t_object *obj, t_csg *csg, t_ray *ray, float t)
{
	t_collision	*col;

	col = our_malloc(sizeof(t_collision));
	col->point.x = ray->pos->x + ray->dir->x * t;
	col->point.y = ray->pos->y + ray->dir->y * t;
	col->point.z = ray->pos->z + ray->dir->z * t;
	col->obj = csg;
	col->parent_obj = obj; // Not sure if we need this one, but it's here
	col->dist = t; // Not sure about that
	return (col);
}

/*
	Will be called externally using the CSG root:
		recursively calls itself to solve the CSG tree
		If the final result is a collision, it returns it
		Else, it returns NULL
*/
t_collision	*hadron_collider(t_object *obj, t_ray *ray, t_csg *csg)
{
	t_collision	*collision[2];

	if (!csg) // Should never happen, since leaves are the terminal nodes, but just in case
		return (NULL);
	if (csg->type == LEAVE)
		return (collider_switch(obj, ray, csg));
	collision[0] = hadron_collider(obj, ray, csg->left);
	collision[1] = hadron_collider(obj, ray, csg->right);
	if (csg->type == UNION)
		return (collider_union(collision));
	else if (csg->type == INTER)
		return (collider_inter(collision));
	else if (csg->type == DIFF)
	{
		if (collision[0] && !collision[1])
			return (del_collision(collision[1]), collision[0]);
	}
	del_collision(collision[0]);
	del_collision(collision[1]);
	return (NULL);
}
