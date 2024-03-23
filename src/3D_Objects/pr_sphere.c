/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/03/23 14:34:06 by aurban           ###   ########.fr       */
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
	sphere->l->shape.sphere.r = parse_double(params[1]) / 2;
	sphere->l->shape.sphere.r2 = sphere->l->shape.sphere.r * sphere->l->shape.sphere.r;
	parse_rgb(&sphere->l->rgb, params[2]);
	sphere->l->reflect = 0;
	sphere->l->refract = 0;
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
t_collision	*collider_sphere(t_object *obj, t_leave *csg, t_ray *ray)
{
	t_vector		dist_oc; // Distance between the ray origin and the sphere center
	t_pair_double	t;
	double			b;
	double			c;

	// Relative position of the sphere
	dist_oc = (t_vector){\
		ray->pos->x - csg->pos.x, \
		ray->pos->y - csg->pos.y, \
		ray->pos->z - csg->pos.z};

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
	col->norm = vec_new(\
		col->point.x - col->csg->pos.x, \
		col->point.y - col->csg->pos.y, \
		col->point.z - col->csg->pos.z);
	vec_normalize(col->norm);
}
