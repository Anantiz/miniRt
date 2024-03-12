/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_quadratic_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:56 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 15:12:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "pair.h"
#include <math.h>

/*
	Return true if the equation has a solution
	Else return false

	We use a pointer to a t_pair_float to store the solutions
*/
bool	quadratic_solver(float a, float b, float c, t_pair_float *t)
{
	float		delta;
	static int	sample = 0;
	sample++;

	if (a == 0)
	{
		// printf("Quadratic a = 0\n");
		if (b == 0)
			return (false);
		t->t1 = -c / b;
		t->t2 = -c / b;
		return (true);
	}
	delta = (b * b) - (4.0 * a * c);
	if (delta < 0)
	{
		if (sample % 80000 == 0)
			printf("Quadratic delta < 0: %f\n", delta);
		return (false);
	}
	t->t1 = (-b - sqrtf(delta)) / (2.0 * a);
	t->t2 = (-b + sqrtf(delta)) / (2.0 * a);
	if (t->t1 > 0 || t->t2 > 0)
		return (true);
	return (false);
}
