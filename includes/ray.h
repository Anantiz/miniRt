/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:24:34 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/22 10:49:41 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "miniRt.h"

typedef	struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}t_ray;

typedef struct s_screen
{
	float	height_factor;
	float	width_factor;

}t_screen;


t_ray		*new_ray(t_camera *camera, float x, float y);


#endif