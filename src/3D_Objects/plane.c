/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 17:22:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_csg	*new_plane(char **params)
{
	t_csg	*plane;

	(void)params;
	plane = our_malloc(sizeof(t_csg));
	// plane->type = PLANE;
	// plane->normal = new_vector(0, 1, 0);
	// plane->point = new_vector(0, 0, 0);
	return (plane);
}

t_collision			*collider_plane(t_object *obj, t_csg *csg, t_ray *ray)
{
	(void)obj;
	(void)csg;
	(void)ray;
	return (NULL);
}
