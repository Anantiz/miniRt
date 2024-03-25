/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/03/25 16:25:55 by aurban           ###   ########.fr       */
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
If params len is not 2, segfault, please give me the right params
	params[0] = diameter
	params[1] = color
*/
t_csg	*pr_new_sphere(t_vector coordinates[2], char **params)
{
	t_csg		*sphere;

	sphere = our_malloc(sizeof(t_csg));
	sphere->type = LEAF;
	sphere->l = our_malloc(sizeof(t_leaf));
	sphere->l->type = SPHERE;
	sphere->l->pos = coordinates[0];
	sphere->l->dir = coordinates[1];
	if (!parse_double(params[0], &sphere->l->shape.sphere.r))
		return (NULL);
	sphere->l->shape.sphere.r /= 2;
	sphere->l->shape.sphere.r2 = sphere->l->shape.sphere.r * sphere->l->shape.sphere.r;
	if (!parse_rgb(&sphere->l->rgb, params[1]))
		return (NULL);
	sphere->l->reflect = 0;
	sphere->l->refract = 1.5;
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
t_collision	*collider_sphere(t_object *obj, t_leaf *csg, t_ray *ray)
{
	t_vector		dist_oc; // Distance between the ray origin and the sphere center
	t_pair_double	t;
	double			b;
	double			c;

	// Relative position of the sphere
	dist_oc = vsub(ray->pos, &csg->pos);

	// A = 1
	b = 2 * vec_dot_product(&dist_oc, ray->dir);
	c = vec_dot_product(&dist_oc, &dist_oc) - (csg->shape.sphere.r2);
	if (!quadratic_solver(1, b, c, &t))
		return (NULL);
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
	col->norm = vsub(&col->point, &col->csg->pos );
	vec_normalize(&col->norm);
}
