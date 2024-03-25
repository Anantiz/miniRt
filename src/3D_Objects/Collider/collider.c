/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:20:27 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:16:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_collision	*new_collision(t_object *obj, t_leaf *csg, t_ray *ray, double t)
{
	t_collision	*col;

	col = our_malloc(sizeof(t_collision));
	col->obj = obj;
	col->csg = csg;
	col->ray = ray;
	col->t = t;
	col->point.x = ray->pos->x + ray->dir->x * t;
	col->point.y = ray->pos->y + ray->dir->y * t;
	col->point.z = ray->pos->z + ray->dir->z * t;
	collision_norm_switch(col, csg->type);
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
	t_collision	*collisions[2];

	if (!csg) // Should never happen, since leaves are the terminal nodes, but just in case
		return (NULL);
	if (csg->type == LEAF)
		return (collider_switch(obj, ray, csg));
	collisions[0] = hadron_collider(obj, ray, csg->left);
	collisions[1] = hadron_collider(obj, ray, csg->right);
	if (csg->type == UNION)
		return (collider_union(collisions));
	else if (csg->type == INTER)
		return (collider_inter(collisions));
	else if (csg->type == DIFF)
		return (collider_diff(collisions));
	return (NULL);
}

