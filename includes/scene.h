/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:16 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 12:20:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <stdbool.h>
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

typedef struct s_object
{
	t_vector	origin;
	t_shape		shape;
	t_mp		properties;
	t_texture	texture;
	t_rgb		color;
	bool		is_light_source;
	int			lumen;
}t_object;


#endif