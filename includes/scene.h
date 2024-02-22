/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 10:40:04 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The Scene will store all the objects and the lights.

	Public functions:	(for initailization and collision query)
		- scene_collision_query
		- scene_add_object
		- update_lumen_distance

	Any other function should not be used outside of the scene module.

Note:
	Yeah, for some stupid reason our vector module follows <service>_vector
	but the scene module follows scene_<service>, don't ask me why.
*/

#ifndef SCENE_H
# define SCENE_H

# include "color_texture.h"
# include "vector.h"
# include <stdbool.h>

// Ugly to put this one here, but we do not have a ray.h
# include "miniRt.h"

/*
	Filler data, much more complex in the future
*/
typedef struct s_shape
{
	float	radius;
	float	height;
	float	width;
	float	depth;
}t_shape;

typedef t_colision *(*t_get_colision)\
(t_vector origin, t_shape shape, t_ray *ray);

/*
	Holds all the data for an object
	get_colision is a function pointer to the object's collision function
	since every shapes have different 3D formulas

	For light sources, the light_intensity and light_lumen are set
	For other objects, the material and texture are set
	they are mutually exclusive (not really)
*/
typedef struct s_object
{
	int					id;
	bool				is_light_source;
	float				light_intensity;
	int					light_lumen;
	t_vector			origin;
	t_shape				shape;
	t_rgb				color;
	t_mp				material;
	t_texture			texture;
	t_get_colision		get_colision;
}t_object;

/*
	Returned by a collision query
	Contains the object and the point of collision for the given ray
*/
typedef struct	s_collision
{
	t_vector		*point;
	const t_object	*object;
}t_colision;

typedef struct s_ll_obj
{
	const t_object		*o;
	struct s_ll_obj		*next;
}t_ll_obj;

/*	Will hold a list of object, there won't be many
	so an unoptimized linked list will do the job
*/
typedef struct s_scene
{
	t_ll_obj		*objects;
	t_rgb			ambiant_rgb;
	int				objects_count;
	float			ambient_light_intensity;
}t_scene;

/* CORE : public */

t_scene				*scene_new(void);
t_colision			*scene_collision_query(t_scene *scene, t_ray *ray);

/* Shapes : private */


/* Mico-service funcionts : public */

void				scene_add_object(t_scene *scene, t_object *object);
int					update_lumen_distance(t_ray *ray, t_vector *point);

/* Trash : private */

t_ll_obj			*tll_add_back(t_ll_obj **head_, t_ll_obj *node);
t_ll_obj			*tll_new_node(t_object *object);
void				tll_del_node(t_ll_obj **root, t_ll_obj *node_);
void				tll_del_list(t_ll_obj **root);

#endif