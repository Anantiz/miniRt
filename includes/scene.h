/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/27 17:27:42 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The Scene will store all the objects and the lights.

	Public functions:	(for initailization and collision query)
		- query_obj_collision
		- scene_add_object
		- update_lumen_distance

	Any other function should not be used outside of the scene module.

Note:
	Yeah, for some stupid reason our vector module follows <service>_vector
	but the scene module follows scene_<service>, don't ask me why.
*/

#ifndef SCENE_H
# define SCENE_H

# include <stdbool.h>

# include "color_texture.h"
# include "vector.h"
# include "ray.h"
# include "_3Dshapes.h"
# include "light.h"

// Either a light or an object, no need to make two structs
// They won't be in the same list anyway
typedef struct s_ll_obj
{
	t_object			*o;
	t_spot_light		*l;
	struct s_ll_obj		*next;
}t_ll_obj;

/*	Will hold a list of object, there won't be many
	so an unoptimized linked list will do the job
*/
typedef struct s_scene
{
	t_ll_obj		*objects;
	t_ll_obj		*lights;

	int				objects_count;
	int				lights_count;

	t_rgb			ambiant_rgb;
	float			amb_intensity;
}t_scene;


/* CORE : public */

t_scene				*scene_new(void);
t_scene				*scene_getter(t_scene *scene);
t_collision			*query_collision(t_scene *scene, t_ray *ray);
t_lcol				*query_visible_light(t_csg *obj , t_vector *point, \
t_vector *ray_dir);


/* Warpers */

void				scene_add_object(t_scene *scene, t_object *object);
void				scene_add_light(t_scene *scene, t_spot_light *light);

/* Mico-services functions : public */

// t_object			*scene_new_object(t_glob *glob);
// void				scene_add_object(t_scene *scene, t_object *object);
// void				scene_add_light(t_scene *scene, t_spot_light *light);
float				update_lumen_distance(float distance, float lumen);

/* Trash : private */

t_ll_obj			*tll_new_node(t_object *object);
t_ll_obj			*tll_new_spot_node(t_spot_light *light);
t_ll_obj			*tll_add_back(t_ll_obj **head_, t_ll_obj *node);

void				tll_del_node(t_ll_obj **root, t_ll_obj *node_);
void				tll_del_list(t_ll_obj **root);

#endif