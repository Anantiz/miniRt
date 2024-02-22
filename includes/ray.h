/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:24:34 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/22 10:25:48 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef	struct s_ray
{
	t_vector	*origin;
	t_vector	*direction;
}				t_ray;

t_ray		*new_ray(t_camera *camera, float x, float y);


#endif