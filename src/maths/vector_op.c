/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:04 by loris             #+#    #+#             */
/*   Updated: 2024/03/11 09:41:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"
#include <math.h>

t_vector    *vec_new(float x, float y, float z)
{
    t_vector	*vector;

	vector = our_malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*vec_add(t_vector *v1, t_vector *v2)
{
	t_vector	*result;

	result = vec_new(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (result);
}

t_vector	*vec_cross_product(t_vector *v1, t_vector *v2)
{
	t_vector	*ret;

	ret = vec_new(v1->y * v2->z - v1->z * v2->y, \
					(v1->x * v2->z) + v1->z * v2->x, \
					(v1->x * v2->y) - v1->y * v2->x);
	return (ret);
}

float	vec_length(t_vector *vector)
{
	float	ret;

	ret = sqrtf((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
	return (ret);
}

void	vec_normalize(t_vector *vector)
{
	float	length;

	length = vec_length(vector);
	if (length == 0)
		return ;
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
}

/*
In all logic, the cosing of the dot product should be an angle in radians

Using a trigonometric circle to think about it:
	Plugging the dot_product in cos gives us the angle between the two vectors.

	Since cos(0) = 1,
		a dot product of 0 means the vectors do not share any axis (orthogonal)
	Following: cos(1) = 0,
		a dot product of 1 means the vectors are on the same axis (parallel)
*/
float	vec_dot_product(t_vector *v1, t_vector *v2)
{
	float	ret;

	ret = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (ret);
}
