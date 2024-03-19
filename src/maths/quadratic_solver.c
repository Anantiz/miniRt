/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_quadratic_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:05:56 by aurban            #+#    #+#             */
/*   Updated: 2024/03/07 13:32:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "pair.h"
#include <math.h>
#include <miniRt.h>

/*
	Return true if the equation has a solution
	Else return false

	We use a pointer to a t_pair_double to store the solutions
*/
bool	quadratic_solver(double a, double b, double c, t_pair_double *t)
{
	double		delta;

	if (a == 0)
	{
		if (b == 0)
			return (false);
		t->t1 = -c / b;
		t->t2 = -c / b;
		return (true);
	}
	delta = (b * b) - (4.0 * a * c);
	if (delta < 0)
		return (false);
	t->t1 = (-b - sqrtf(delta)) / (2.0 * a);
	t->t2 = (-b + sqrtf(delta)) / (2.0 * a);
	if (t->t1 > EPSILON || t->t2 > EPSILON)
		return (true);
	return (false);
}
