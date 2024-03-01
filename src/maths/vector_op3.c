/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:51:00 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 12:47:55 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	ft_bound_float(float value, float max, float min)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

float		vec_get_angle_rad(t_vector *v1, t_vector *v2)
{
	t_vector	normed1;
	t_vector	normed2;
	float		temp;

	temp = vector_length(v1);
	if (temp == 0)
		normed1 = (t_vector){1, 1, 1};
	else
		normed1 = (t_vector){v1->x / temp, v1->y / temp, v1->z / temp};
	temp = vector_length(v2);
	if (temp == 0)
		normed2 = (t_vector){1, 1, 1};
	else
		normed2 = (t_vector){v2->x / temp, v2->y / temp, v2->z / temp};
	return ((\
	ft_bound_float(vec_dot_product(v1, v2), 1, -1) \
	/ (ft_bound_float(vec_dot_product(&normed1, &normed2), 1, -1) + EPSILON)));
}

// return true if a and b are close enough
bool	fcmp(float a, float b)
{
	bool	abs_diff;
	bool	sign_diff;

	abs_diff = fabs(a - b) < EPSILON;
	sign_diff = (a < 0) == (b < 0);
	return (abs_diff && sign_diff);
}

bool	vec_cmp(t_vector *v1, t_vector *v2)
{
	if (fcmp(v1->x, v2->x) && fcmp(v1->y, v2->y) && fcmp(v1->z, v2->z))
		return (false);
	return (true);
}
