/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:51:17 by aurban            #+#    #+#             */
/*   Updated: 2024/03/23 21:14:14 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// return true if a and b are close enough
bool	ft_fcmp(double a, double b)
{
	if (a > 0 && b < 0)
		return (false);
	if (a < 0 && b > 0)
		return (false);
	return (fabs(a - b) < EPSILON);
}

double	ft_bound_double(double value, double max, double min)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}
