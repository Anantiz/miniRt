/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_solver.c                                 :+:      :+:    :+:   */
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
Args:
	t: The pair of float that will contain the two solutions
	Dist_oc: Dist between the origin of the ray and the origin of the circle
	Dir: Direction of the incoming ray
	r: Radius of the circle
Return:
	True if there is a solution, false otherwise
*/
bool	quadratic_solver(t_pair_float *t, t_vector *dist_oc, \
t_vector *dir, float r)
{
	float		b;
	float		c;
	float		delta;

	// We assume that the ray is normalized, thus a = 1
	// This might cause Doomsday if it's not the case *shrug*
	b = 2.0 * vec_dot_product(dist_oc, dir);
	c = vec_dot_product(dist_oc, dist_oc) - (r * r);
	delta = (b * b) - (4.0 * c);
	if (delta < 0)
		return (false);
	t->t1 = (b - sqrtf(delta)) / (2.0);
	t->t2 = (b + sqrtf(delta)) / (2.0);
	if (t->t1 > 0 || t->t2 > 0)
		return (true);
	return (false);
}
