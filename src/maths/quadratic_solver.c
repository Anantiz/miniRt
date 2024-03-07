/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_solver.c                                 :+:      :+:    :+:   */
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


/*
Terms:
	A = 1 (normalized vector)
	B = 2 * (O - R⃗c)⋅D⃗
	C = (O - R⃗c)⋅(O - R⃗c) - r²
	With:
		O = ray->pos		// Origin of the ray
		R⃗c = csg->l->pos	// Center of the sphere
		D⃗ = ray->dir		// Direction of the ray
		r = csg->l->shape.sphere.rad // Radius of the sphere
t_collision	*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		dist_oc; // Distance between the ray origin and the sphere center
	t_pair_float	t;

	dist_oc = (t_vector){\
		obj->pos.x + csg->l->pos.x - ray->pos->x, \
		obj->pos.y + csg->l->pos.y - ray->pos->y, \
		obj->pos.z + csg->l->pos.z - ray->pos->z};

	dist_oc is correct
	if (!quadratic_solver(1, (2 * vec_dot_product(&dist_oc, ray->dir)), \
	(vec_dot_product(&dist_oc, &dist_oc) - (csg->l->shape.sphere.rad * \
	csg->l->shape.sphere.rad)), &t))
	{
		return (NULL);
	}
	if (t.t1 < 0 || (t.t2 > 0 && t.t2 < t.t1))
		return (new_collision(obj, csg, ray, t.t2));
	return (new_collision(obj, csg, ray, t.t1));
}
*/