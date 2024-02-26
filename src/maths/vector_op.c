/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:04 by loris             #+#    #+#             */
/*   Updated: 2024/02/26 15:08:23 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"
#include <math.h>

t_vector    *new_vector(float x, float y, float z)
{
    t_vector	*vector;

	vector = our_malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector	*add_vector(t_vector *v1, t_vector *v2)
{
	t_vector	*result;

	result = new_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (result);
}

t_vector	*produit_vectoriel(t_vector *v1, t_vector *v2)
{
	t_vector	*ret;

	ret = new_vector(v1->y * v2->z - v1->z * v2->y, \
					(v1->x * v2->z) + v1->z * v2->x, \
					(v1->x * v2->y) - v1->y * v2->x);
	return (ret);
}

float	vector_length(t_vector *vector)
{
	float	ret;

	ret = sqrtf((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
	return (ret);
}

void	vector_normalizer(t_vector *vector)
{
	float	length;

	length = vector_length(vector);
	if (length == 0)
		return ;
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
}

float	vec_dot_product(t_vector *v1, t_vector *v2)
{
	float	ret;

	ret = ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
	return (ret);
}
