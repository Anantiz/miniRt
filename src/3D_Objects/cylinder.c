/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 17:22:52 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_csg	*new_cylinder(char **params)
{
	t_csg	*cylinder;

	(void)params;
	cylinder = our_malloc(sizeof(t_csg));
	// cylinder->type = CYLINDER;
	// cylinder->point = new_vector(0, 0, 0);
	// cylinder->normal = new_vector(0, 1, 0);
	// cylinder->diameter = 1;
	// cylinder->height = 1;
	return (cylinder);
}

t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	(void)obj;
	(void)csg;
	(void)ray;
	return (NULL);
}