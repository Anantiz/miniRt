/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 07:20:27 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 07:30:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_colision	*new_collision(t_object *obj, t_csg *csg, t_ray *ray, float t)
{
	t_colision	*col;

	col = our_malloc(sizeof(t_colision));
	col->point.x = ray->origin->x + ray->direction->x * t;
	col->point.y = ray->origin->y + ray->direction->y * t;
	col->point.z = ray->origin->z + ray->direction->z * t;
	col->obj = csg;
	col->parent_obj = obj; // Not sure if we need this one, but it's here
	col->dist = t;
	return (col);
}
