/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/03/07 13:30:16 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Pr constructors are given correct parameters, so we don't need to check them
they are already checked in the parsing process

Primitive constructors take their relative position in last as they are optional
0 if not set
*/

/*
If params len is not 3, segfault, please give me the right params
	params[0] = pos
	params[1] = diameter
	params[2] = color
*/
t_csg	*pr_new_sphere(char **params)
{
	t_csg		*sphere;

	if (ft_tablen(params) != 3)
		error_exit("Wrong parameters count : Sphere : pr_new_");
	sphere = our_malloc(sizeof(t_csg));
	sphere->type = LEAVE;
	sphere->l = our_malloc(sizeof(t_leave));
	sphere->l->type = SPHERE;
	sphere->l->dir = (t_vector){0, 0, 0};
	parse_position(&sphere->l->pos, params[0]);
	sphere->l->shape.sphere.rad = parse_float(params[1]) / 2;
	parse_rgb(&sphere->l->rgb, params[2]);
	return (sphere);
}

/*
First we convert the sphere into a polynomial equation
(The params sent to the quadratic solver)
Then we solve the quadratic equation
And we return the collision

Super compact version of the function, to make it faster (less memory allocation)
(We only work on the CPU bruh)

Terms:
	A = 1 (normalized vector)
	B = 2 * (O - R⃗c)⋅D⃗
	C = (O - R⃗c)⋅(O - R⃗c) - r²
	With:
		O = ray->pos		// Origin of the ray
		R⃗c = csg->l->pos	// Center of the sphere
		D⃗ = ray->dir		// Direction of the ray
		r = csg->l->shape.sphere.rad // Radius of the sphere
*/
t_collision	*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		dist_oc; // Distance between the ray origin and the sphere center
	t_pair_float	t;

	dist_oc = (t_vector){\
		obj->pos.x + csg->l->pos.x - ray->pos->x, \
		obj->pos.y + csg->l->pos.y - ray->pos->y, \
		obj->pos.z + csg->l->pos.z - ray->pos->z};
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
