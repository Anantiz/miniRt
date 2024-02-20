/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:04 by loris             #+#    #+#             */
/*   Updated: 2024/02/20 14:09:51 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector    *new_vector(float x, float y, float z)
{
    t_vector	*vector;

	vector = our_malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*addition(t_vector *v1, t_vector *v2)
{
	t_vector	*result;

	result = new_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (result);
}

float	vector_length(t_vector *vector)
{
	float	ret;

	ret = sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
	return (ret);
}

void	vector_normalizer(t_vector *vector)
{
	float	length;

	length  = vector_length(vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

float	vec_dot_product(t_vector *v1, t_vector *v2)
{
	float	ret;

	ret = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (ret);
}