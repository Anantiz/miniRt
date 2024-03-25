/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:33 by aurban            #+#    #+#             */
/*   Updated: 2024/03/25 09:35:57 by lkary-po         ###   ########.fr       */
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
	fetch_scene(scene);
	return (scene);
}

static void	free_collisions_except(t_collision **collisions, t_collision *except, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (collisions[i] != except)
			our_free(collisions[i]);
	}
	our_free(collisions);
}

static t_collision	*get_closest_collision(t_collision **collisions, int count)
{
	t_collision *closest_collision;
	float		closest_dist;
	int			i;

	closest_dist = FLT_MAX;
	closest_collision = NULL;
	i = -1;
	while (++i < count)
	{
		if (collisions[i])
		{
			if (collisions[i]->dist < closest_dist)
			{
				closest_dist = collisions[i]->dist;
				closest_collision = collisions[i];
			}
		}
	}
	free_collisions_except(collisions, closest_collision ,count);
	return (closest_collision);
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
t_collision	*query_collision(t_scene *scene, t_ray *ray)
{
	t_ll_obj	*obj;
	t_collision	**collisions;
	int			i;

	collisions = our_malloc(sizeof(t_collision *) * (scene->objects_count));
	obj = scene->objects;
	i = 0;
	while (obj) // Get collisions with all objects
	{
		collisions[i++] = hadron_collider(obj->o, ray, obj->o->csg);
		obj = obj->next;
	}
	return (get_closest_collision(collisions, scene->objects_count));
}
