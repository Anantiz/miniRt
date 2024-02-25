/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:33 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 08:23:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
For error handling, the light intensity is set to -1.0f
if after parsing, the ambiant light intensity is still -1.0f
then the program will exit with an error message
*/
t_scene	*scene_new(void)
{
	t_scene	*scene;

	scene = our_malloc(sizeof(t_scene));
	scene->objects = NULL;
	scene->objects_count = 0;
	scene->lights = NULL;
	scene->lights_count = 0;
	scene->ambiant_rgb = (t_rgb){0, 0, 0};
	scene->amb_intensity = -1.0f;
	return (scene);
}

/*
Note:
	This function does update the `lumen' field of the ray
	based on the distance between the ray's origin and the colision point
	and returns a NULL colision if the lumen is 0 (too far)...
Return:
	No collision found
		-> NULL
	Collision found
		-> t_colision
*/

// OBSOLETE
// t_collision	*scene_collision_query(t_scene *scene, t_ray *ray)
// {
// 	t_ll_obj	*obj;
// 	t_collision	*collision;

// 	obj = scene->objects;
// 	collision = NULL;
// 	while (obj)
// 	{
// 		collision = obj->o->get_collision(&obj->o->origin, &obj->o->shape, ray);
// 		if (collision)
// 		{
// 			ray->lumen = update_lumen_distance(ray, collision->point);
// 			if (ray->lumen == 0)
// 				return (our_free(collision), NULL);
// 			return (collision);
// 		}
// 		obj = obj->next;
// 	}
// 	return (NULL);
// }
