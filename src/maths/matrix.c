/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:58:34 by aurban            #+#    #+#             */
/*   Updated: 2024/03/23 20:46:59 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
	Returns the angles to rotate v into the z-axis using a rotation matrix
*/
void	vec_allign_zaxis(double theta[3], t_vector *v)
{
	theta[0] = atan2(v->y, v->z);
	theta[1] = -atan2(v->x, v->z);
	theta[2] = 0;
}

/*
	Returns a new_vector that is the result of rotating v by theta
*/
t_vector	*vec_matrix_rotate(t_vector *v, double theta[3])
{
	t_vector 	*ret;
	double		trig_x[2];
	double		trig_y[2];
	double		trig_z[2];

	ret = our_malloc(sizeof(t_vector));
	trig_x[0] = cos(theta[0]);
	trig_x[1] = sin(theta[0]);
	trig_y[0] = cos(theta[1]);
	trig_y[1] = sin(theta[1]);
	trig_z[0] = cos(theta[2]);
	trig_z[1] = sin(theta[2]);
	ret->x = v->x * (trig_y[0] * trig_z[0]) \
			+ v->y * (trig_x[1] * trig_y[1] * trig_z[0] - trig_x[0] * trig_z[1]) \
			+ v->z * (trig_x[0] * trig_y[1] * trig_z[0] + trig_x[1] * trig_z[1]);

	ret->y = v->x * (trig_y[0] * trig_z[1]) \
			+ v->y * (trig_x[1] * trig_y[1] * trig_z[1] + trig_x[0] * trig_z[0]) \
			+ v->z * (trig_x[1] * trig_y[0] * trig_z[1] - trig_x[1] * trig_z[0]);

	ret->z = v->x * (-trig_y[1]) \
			+ v->y * (trig_x[1] * trig_y[0]) \
			+ v->z * (trig_x[0] * trig_y[0]);
	return (ret);
}

t_vector	*vec_matrix_rev_rotate(t_vector *v, double theta[3])
{
	t_vector *ret;
	double	cos[3];
	double	sin[3];
	double	xyz_temp[3];

	ret = our_malloc(sizeof(t_vector));
	cos[0] = cosf(theta[0]);
	cos[1] = cosf(theta[1]);
	cos[2] = cosf(theta[2]);
	sin[0] = sinf(theta[0]);
	sin[1] = sinf(theta[1]);
	sin[2] = sinf(theta[2]);
	xyz_temp[1] = v->y * cos[2] - v->z * sin[2];
	xyz_temp[2] = v->y * sin[2] + v->z * cos[2];
	xyz_temp[0] = v->x * cos[1] - xyz_temp[2] * sin[1];
	ret->x = xyz_temp[0] * cos[0] + xyz_temp[1] * sin[0];
	ret->y = -xyz_temp[0] * sin[0] + xyz_temp[1] * cos[0];
	ret->z = xyz_temp[2] * cos[1]; // Z-axis rotation result
	return (ret);
}
