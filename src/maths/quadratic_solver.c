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

/*
	Return true if the equation has a solution
	Else return false

	We use a pointer to a t_pair_float to store the solutions
*/
bool	quadratic_solver(float a, float b, float c, t_pair_float *t)
{
	float		delta;
	// static int	sample = 0;

	// sample++;
	if (a == 0)
	{
		// if (sample % 20000 == 0)
		// 	printf("Quadratic a = 0, b=%f	c=%f\n",b,c);
		if (b == 0)
			return (false);
		t->t1 = -c / b;
		t->t2 = -c / b;
		return (true);
	}
	delta = (b * b) - (4.0 * a * c);
	if (delta < 0)
	{
		// if (sample % 20000 == 0)
		// 	printf("Quadratic delta < 0: %f\ta=%f\tb=%f\tc=%f\n", delta,a,b,c);
		return (false);
	}
	t->t1 = (-b - sqrtf(delta)) / (2.0 * a);
	t->t2 = (-b + sqrtf(delta)) / (2.0 * a);
	if (t->t1 > EPSILON || t->t2 > EPSILON)
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