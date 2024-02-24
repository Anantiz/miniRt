/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:49:46 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 11:17:38 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

/*
	Shall not return NULL
	Because we are not in the mood for error handling
*/
t_vector	*cpy_vector(t_vector *v)
{
	t_vector	*ret;

	ret = our_malloc(sizeof(t_vector));
	if (v)
	{
		ret->x = v->x;
		ret->y = v->y;
		ret->z = v->z;
	}
	else
	{
		ret->x = 0;
		ret->y = 0;
		ret->z = 0;
	}
	return (ret);
}

t_vector	*sub_vector(t_vector *v1, t_vector *v2)
{
	t_vector	*ret;

	ret = our_malloc(sizeof(t_vector));
	ret->x = v1->x - v2->x;
	ret->y = v1->y - v2->y;
	ret->z = v1->z - v2->z;
	return (ret);
}

/*
	Use this to avoid memory leaks
	(throwing everything for the garbage collector is ugly)
*/
void	rea_v(t_vector **old_addr, t_vector *new_ptr)
{
	our_free(*old_addr);
	*old_addr = new_ptr;
}

float	dist_vector(const t_vector *v1, const t_vector *v2)
{
	float	x;
	float	y;
	float	z;

	x = v1->x - v2->x;
	y = v1->y - v2->y;
	z = v1->z - v2->z;
	return (sqrtf(x * x + y * y + z * z));
}

t_vector	*mult_vector(float k, t_vector *v1)
{
	t_vector	*ret;

	ret = new_vector(v1->x * k, v1->y * k, v1->z * k);
	return (ret);
}