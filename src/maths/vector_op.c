/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:44:04 by loris             #+#    #+#             */
/*   Updated: 2024/03/19 12:44:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*vec_new(double x, double y, double z)
{
	t_vector	*vector;

	vector = our_malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

/*
	Shall not return NULL
	Because we are not in the mood for error handling
*/
t_vector	*vec_copy(t_vector *v)
{
	t_vector	*ret;

	ret = our_malloc(sizeof(t_vector));
	if (v)
		*ret = (t_vector){v->x, v->y, v->z };
	else
		*ret = (t_vector){0, 0, 0};
	return (ret);
}

/*
	Use this to avoid memory leaks
	(throwing everything for the garbage collector is ugly)
*/
t_vector	*vec_realloc(t_vector **old_addr, t_vector *new_ptr)
{
	our_free(*old_addr);
	*old_addr = new_ptr;
	return (new_ptr);
}

t_vector	*vec_cross_product(t_vector *v1, t_vector *v2)
{
	return (vec_new(v1->y * v2->z - v1->z * v2->y, \
					(v1->x * v2->z) + v1->z * v2->x, \
					(v1->x * v2->y) - v1->y * v2->x));
}

/*
Assuming a normalized vector -- ONLY
In all logic, the cosing of the dot product should be an angle in radians

Using a trigonometric circle to think about it:
	Plugging the dot_product in cos gives us the angle between the two vectors.

	Since cos(0) = 1,
		a dot product of 0 means the vectors do not share any axis (orthogonal)
	Following: cos(1) = 0,
		a dot product of 1 means the vectors are on the same axis (parallel)
*/
double	vec_dot_product(t_vector *v1, t_vector *v2)
{
	return (((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z)));
}
