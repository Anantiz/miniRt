/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 00:24:18 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 16:18:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>

# include "../libs/MLX42/include/MLX42/MLX42_Int.h"
# include "scene.h"
# include "libft.h"
# include "vector.h"
# include "pair.h"

typedef	struct	s_camera
{
	t_vector	*pos;
	t_vector	*direction;
	t_vector	*right;
	t_vector	*up;
	double		fov;
}t_camera;

typedef	struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}t_ray;

typedef struct s_glob
{
	t_camera		*camera;
	mlx_t			*mlx;
	mlx_image_t		*mlx_img;
	t_scene			*scene;
}t_glob;


#endif
