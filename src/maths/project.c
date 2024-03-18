/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:00:17 by aurban            #+#    #+#             */
/*   Updated: 2024/03/18 13:32:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
	Project a onto b

	Formula:
	((a dot b) / (b dot b)) * b
*/
t_vector	*vec_project(t_vector *a, t_vector *b)
{
	t_vector	*ret;

	ret = vec_copy(b);
	vec_normalize(ret);
	return (vec_realloc(&ret, \
	vec_mult(vec_dot_product(a, b) / vec_dot_product(b, b), ret)));
}

/*
	Get the distance between two vectors (points) along a direction
	a negative result means that to get from a to b, you have to go backwards
	the direction vector.

	The direction is calculated as follow:
		-Take the vectors angle with the origin
		If b's angle is greater than a's angle, the direction is positive
		Else, the direction is negative
		(We assume that if te angle is over 180°, we take negative angles
		so 181° is -179°, we then take the absolute value of the angle,
		In others terms, we split the trigonometric circle in two halves
		and if B is closer towards the right-half than A it is a positive dist
		otherwise it is a negative dist)

	BUT, since we have 3D vectors, we have to work with dot products
	So angle <-> dot equvialents:
		If dot b > dot a then it's positive
		Else, it's negative


	Note:
		since the dot product with the origin is always 0, we just take a
		given vector (3D makes thing harder ...)
*/
float	signed_dist(t_vector *a, t_vector *b, t_vector *dir)
{
	dir = vec_copy(dir); // We don't want to modify the original vector
	vec_normalize(dir);
	if (vec_dot_product(b, dir) > vec_dot_product(a, dir))
		return (vec_dist(a, b));
	return (-vec_dist(a, b));
}

/*
	Return the smallest positive value between a and b
	(If both are negative, return b)
*/
float	smallest_pos(float a, float b)
{
	if (a < 0 || (b > 0 && b < a))
		return (b);
	else
		return (a);
}

/*
	Returns a new_vector that is passed through a rotation
	matrix built from the given angles
*/
t_vector	*vec_matrix_rotate(t_vector *v, float theta[3])
{
	t_vector *ret;
	float	cos[3];
	float	sin[3];
	float	temp[3];

	ret = our_malloc(sizeof(t_vector));
	cos[0] = cosf(theta[0]);
	cos[1] = cosf(theta[1]);
	cos[2] = cosf(theta[2]);
	sin[0] = sinf(theta[0]);
	sin[1] = sinf(theta[1]);
	sin[2] = sinf(theta[2]);
	temp[1] = v->y * cos[0] - v->z * sin[0];
	temp[2] = v->y * sin[0] + v->z * cos[0];
	temp[0] = v->x * cos[1] + temp[2] * sin[1];
	ret->x = temp[0] * cos[2] - temp[1] * sin[2];
	ret->y = temp[0] * sin[2] + temp[1] * cos[2];
	ret->z = -v->x * sin[1] + temp[2] * cos[1]; // Z-axis rotation result
	return (ret);
}
