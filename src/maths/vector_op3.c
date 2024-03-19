/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:51:00 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 12:44:45 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vec_abs(t_vector *v)
{
	v->x = fabs(v->x);
	v->y = fabs(v->y);
	v->z = fabs(v->z);
}

t_vector	*vec_negate(t_vector *v)
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
	return (v);
}

double	vec_len(t_vector *vector)
{
	return (sqrtf((vector->x * vector->x) \
			+ (vector->y * vector->y) \
			+ (vector->z * vector->z)));
}

void	vec_normalize(t_vector *vector)
{
	double	length;

	length = vec_len(vector);
	if (length == 0)
		return ;
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
}

bool	vec_cmp(t_vector *v1, t_vector *v2)
{
	if (fcmp(v1->x, v2->x) && fcmp(v1->y, v2->y) && fcmp(v1->z, v2->z))
		return (false);
	return (true);
}
