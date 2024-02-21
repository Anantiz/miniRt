/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 13:47:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdbool.h>
# include "./miniRt.h"
# include "./vector.h"
# include "./color_texture.h"

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

typedef struct s_object
{
	t_vector		origin;
	t_shape			shape;
	t_mp			properties;
	t_texture		texture;
	t_rgb			color;
	bool			is_light_source;
	t_get_colision	get_colision;
}t_object;

typedef struct	s_collision
{
	t_vector	*point;
	t_object	*object;
}t_colision;

typedef struct s_ll_obj
{
	t_object		*o;
	struct s_ll_obj	*next;
}t_ll_obj;

typedef struct s_scene
{
	t_ll_obj	*objects;
	int			objects_count;
}t_scene;

/* CORE : public */

t_colision			*scene_collision_query(t_glob *scene, t_ray *ray);

/* Shapes : private */

/* Utils : private*/

void				scene_add_object(t_glob *glob, t_object *object);

/* Trash : private */

t_ll_obj			*tll_add_back(t_ll_obj **head_, t_ll_obj *node);
t_ll_obj			*tll_new_node(t_object *object);
void				tll_del_node(t_ll_obj **root, t_ll_obj *node_);
void				t_env_del_list(t_ll_obj **root);


#endif