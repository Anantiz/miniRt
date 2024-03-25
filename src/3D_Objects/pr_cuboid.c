/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cuboid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:04:58 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:16:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
When Calling the function:
	params[0] = Height
	params[1] = Width
	params[2] = Depth
	params[3] = Color

	The duboid *Direction* goes towards the depth
*/
t_csg	*pr_new_cuboid(t_vector coordinates[2], char **params)
{
	t_csg	*cb;

	cb = malloc(sizeof(*cb));
	cb->type = LEAF;
	cb->l = malloc(sizeof(*cb->l));
	cb->l->type = CUBOID;
	cb->l->pos = coordinates[0];
	cb->l->dir = coordinates[1];
	if (!parse_double(params[0], &cb->l->shape.cuboid.h))
		return (NULL);
	if (!parse_double(params[1], &cb->l->shape.cuboid.w))
		return (NULL);
	if (!parse_double(params[2], &cb->l->shape.cuboid.d))
		return (NULL);
	if (!parse_rgb(&cb->l->rgb, params[3]))
		return (NULL);
	cb->l->reflect = 0;
	cb->l->refract = 0;
	cb->l->shape.cuboid.norm_w = cb->l->dir;
	return (cb);
}

t_collision	*collider_cuboid(t_object *obj, t_leaf *csg, t_ray *ray)
{
	t_vector	pos;
	t_vector	dir;
	double		t;

	return (new_collision(obj, csg, ray, t));
}