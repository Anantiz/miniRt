/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:51:17 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 11:56:07 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// return true if a and b are close enough
bool	fcmp(float a, float b)
{
	bool	abs_diff;
	bool	sign_diff;

	abs_diff = fabs(a - b) < EPSILON;
	sign_diff = (a < 0) == (b < 0);
	return (abs_diff && sign_diff);
}

float	ft_bound_float(float value, float max, float min)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}