/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:22:22 by aurban            #+#    #+#             */
/*   Updated: 2024/03/13 15:23:17 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

bool	vec_less_than(t_vector *a, t_vector *b)
{
	return (a->x < b->x && a->y < b->y && a->z < b->z);
}

bool	vec_more_than(t_vector *a, t_vector *b)
{
	return (a->x > b->x && a->y > b->y && a->z > b->z);
}

bool	vec_less_than_or_equal(t_vector *a, t_vector *b)
{
	return (a->x <= b->x && a->y <= b->y && a->z <= b->z);
}

bool	vec_more_than_or_equal(t_vector *a, t_vector *b)
{
	return (a->x >= b->x && a->y >= b->y && a->z >= b->z);
}
