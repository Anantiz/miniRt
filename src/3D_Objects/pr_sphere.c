/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/03/12 18:12:18 by aurban           ###   ########.fr       */
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
	Sphere equation:
	(x - xc)² + (y - yc)² + (z - zc)² = r²
	Plug the ray equation into the sphere equation:
	(O + tD - C)² = r²
	(Ox + tDx - Cx)² + (Oy + tDy - Cy)² + (Oz + tDz - Cz)² = r²
	Solve for t:
	(Ox + tDx - Cx)² + (Oy + tDy - Cy)² + (Oz + tDz - Cz)² - r² = 0

	Also, for some reason I can't figure out, For our spheres , B has to be negated
	I think it's cuz the whole coordinate system is a mess ¯\_(ツ)_/¯
*/
t_collision	*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray)
{
	// static int	sample = 0;

	t_vector		dist_oc; // Distance between the ray origin and the sphere center
	t_pair_float	t;
	float			b;
	float			c;

	// Relative position of the sphere
	dist_oc = (t_vector){\
		ray->pos->x - (obj->pos.x + csg->l->pos.x), \
		ray->pos->y - (obj->pos.y + csg->l->pos.y), \
		ray->pos->z - (obj->pos.z + csg->l->pos.z)};

	// A = 1
	b = 2 * vec_dot_product(&dist_oc, ray->dir);
	c = vec_dot_product(&dist_oc, &dist_oc) - (csg->l->shape.sphere.rad * csg->l->shape.sphere.rad);
	if (!quadratic_solver(1, b, c, &t))
	{
		//DEBUG
		// if (sample++ % 80000 == 0)
		// {
		// 	printf("\033[33mSphere Dead: \033[0m\n");
		// 	printf("\tA: 1 B: %f C: %f\n", b,c);
		// 	printf("\tRadius2: %f\n", csg->l->shape.sphere.rad * csg->l->shape.sphere.rad * (csg->l->shape.sphere.rad * csg->l->shape.sphere.rad));
		// 	printf("\t(O - R⃗c)⋅(O - R⃗c): %f\n", vec_dot_product(&dist_oc, &dist_oc));
		// 	printf("\tDist: %f\n", vec_length(&dist_oc));
		// 	printf("\n");
		// }
		return (NULL);
	}
	//DEBUG
	// if (sample++ % 80000 == 0)
	// {
	// 	printf("\033[33mSphere: \033[0m\n");
	// 	printf("\tt1: %f t2: %f\ndist_oc", t.t1,t.t2);
	// 	printf("\tA: 1 B: %f C: %f\n", b,c);
	// 	printf("\tRadius2: %f\n", csg->l->shape.sphere.rad * csg->l->shape.sphere.rad);
	// 	printf("\t(O - R⃗c)⋅(O - R⃗c): %f\n", vec_dot_product(&dist_oc, &dist_oc));
	// 	printf("\n");
	// }
	if (t.t1 < 0 || (t.t2 > 0 && t.t2 < t.t1))
		return (new_collision(obj, csg, ray, t.t2));
	return (new_collision(obj, csg, ray, t.t1));
}

/*
Norm of a sphere is the vector from the center to the point
*/
void	collider_sphere_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	col->norm = vec_new(\
		col->point.x - (col->parent_obj->pos.x + col->obj->l->pos.x), \
		col->point.y - (col->parent_obj->pos.y + col->obj->l->pos.y), \
		col->point.z - (col->parent_obj->pos.z + col->obj->l->pos.z));
	vec_normalize(col->norm);
}
