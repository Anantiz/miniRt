/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:49:46 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 12:00:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*vec_add(t_vector *v1, t_vector *v2)
{
	return (vec_new(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z));
}

t_vector	*vec_sub(t_vector *v1, t_vector *v2)
{
	return (vec_new(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z));
}

t_vector	*vec_mult(float k, t_vector *v1)
{
	return (vec_new(v1->x * k, v1->y * k, v1->z * k));
}

t_vector	*vec_div(float k, t_vector *v1)
{
	return (vec_new(v1->x / k, v1->y / k, v1->z / k));
}

float	vec_dist(t_vector *v1, t_vector *v2)
{
	float	x;
	float	y;
	float	z;

	x = v1->x - v2->x;
	y = v1->y - v2->y;
	z = v1->z - v2->z;
	return (sqrtf(x * x + y * y + z * z));
}
