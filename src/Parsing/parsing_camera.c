/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 23:14:54 by aurban            #+#    #+#             */
/*   Updated: 2024/03/25 00:56:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

/*
	Parses the right and up vectors of the camera
*/
void	parse_camera_vectors(t_camera *cam)
{
	t_vector	tmp;
	double		theta[2];

	tmp = *cam->dir;
	theta[0] = atan2(tmp.y, tmp.z);
	tmp = mtx_rotate_x(&tmp, theta[0]);
	theta[1] = -atan2(tmp.x, tmp.z);
	tmp = mtx_rotate_y(&tmp, theta[1]);

	tmp = (t_vector){0, 1, 0};
	tmp = mtx_rotate_y(&tmp, -theta[1] - M_PI_2);
	tmp = mtx_rotate_x(&tmp, -theta[0]);
	cam->up = vec_copy(&tmp);
	cam->right = vec_cross_product(cam->up, cam->dir);
}
