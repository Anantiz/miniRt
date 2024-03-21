/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:55:09 by aurban            #+#    #+#             */
/*   Updated: 2024/03/15 16:22:08 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
	Overly complicated function to get the angle between two vectors
	But it works
*/
float		vec_get_angle_axis(t_vector *v1, t_vector *v2)
{
	t_vector	normed1;
	t_vector	normed2;
	float		temp;
	float		angle;

	// Step-1 Safe method to consider zero vectors
	temp = vec_len(v1);
	if (temp == 0)
		return (0);
	else
		normed1 = (t_vector){v1->x / temp, v1->y / temp, v1->z / temp};

	temp = vec_len(v2);
	if (temp == 0)
		return (0);
	else
		normed2 = (t_vector){v2->x / temp, v2->y / temp, v2->z / temp};

	// Step-2 In two parts, make the formula for tetah
	temp = vec_dot_product(&normed1, &normed2);
	// If the dot product is 0, the vectors are perpendicular
	if (temp == 0)
		return (M_PI / 2);
	angle = ft_bound_float(vec_dot_product(v1, v2), 1, -1) / temp;
	return (acosf(angle));
}
