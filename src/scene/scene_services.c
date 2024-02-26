/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_services.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:49:45 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 07:38:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	scene_add_object(t_scene *scene, t_object *object)
{
	t_ll_obj	*node;

	node = tll_new_node(object);
	tll_add_back(&scene->objects, node);
	scene->objects_count++;
}

void	scene_add_light(t_scene *scene, t_spot_light *light)
{
	t_ll_obj	*node;

	node = tll_new_spot_node(light);
	tll_add_back(&scene->lights, node);
	scene->lights_count++;
}
