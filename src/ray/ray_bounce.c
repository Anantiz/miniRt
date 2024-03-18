/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bounce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:26:07 by loris             #+#    #+#             */
/*   Updated: 2024/03/17 15:59:49 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRt.h"

t_collision	*trace_ray(t_ray *ray, t_scene *scene, int deepness)
{
	t_collision	*col;

	col = query_collision(scene, ray);

	if (deepness == 0)
		//return black

	if (!col)
		// return background
	if (col)
	{
		if (reflectivité)

		if (refraction)
	}
}

// ADD the normal to the hit point to each coll
