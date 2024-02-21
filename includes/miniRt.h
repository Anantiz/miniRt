/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 00:24:18 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 12:55:01 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>

# include "../libs/MLX42/include/MLX42/MLX42_Int.h"
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
}				t_camera;

typedef	struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}				t_ray;


#endif
