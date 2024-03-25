/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2inplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:25:59 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 12:44:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*vec_add_inplace(t_vector *v1, t_vector *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
	return (v1);
}

t_vector	*vec_sub_inplace(t_vector *v1, t_vector *v2)
{
	v1->x -= v2->x;
	v1->y -= v2->y;
	v1->z -= v2->z;
	return (v1);
}

t_vector	*vec_mult_inplace(double k, t_vector *v1)
{
	v1->x *= k;
	v1->y *= k;
	v1->z *= k;
	return(v1);
}

t_vector	*vec_div_inplace(double k, t_vector *v1)
{
	v1->x /= k;
	v1->y /= k;
	v1->z /= k;
	return (v1);
}
