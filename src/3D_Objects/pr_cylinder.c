/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 16:13:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
If params len is not 5, segfault, please give me the right params
	params[0] = diameter
	params[1] = height
	params[2] = color
	(optional)params[3] = pos
	(optional)[4] = orientation
*/
t_csg	*pr_new_cylinder(char **params)
{
	t_csg	*cylinder;

	cylinder = our_malloc(sizeof(t_csg));
	cylinder->type = LEAVE;
	cylinder->l = our_malloc(sizeof(t_object));
	cylinder->l->type = CYLINDER;
	cylinder->l->shape.cylinder.rad = ft_atoldb(params[0]) / 2;
	cylinder->l->shape.cylinder.height = ft_atoldb(params[1]);
	parse_rgb(&cylinder->l->rgb, params[2]);
	if (params[3])
		parse_position(&cylinder->l->pos, params[3]);
	else
		cylinder->l->pos = (t_vector){0, 0, 0};
	if (params[4])
		parse_orientation(&cylinder->l->ort, params[4]);
	else
		cylinder->l->ort = (t_vector){0, 0, 0};
	return (cylinder);
}

/*
Cylinder equation:
  (P⃗−C)⋅A⃗ = 0
and
 ∣∣P⃗−C−((P⃗−C)⋅A⃗)⋅A⃗∣∣ ≤ r

with:
P⃗ = point on the cylinder
C⃗ = center of the cylinder
A⃗ = axis of the cylinder
r = radius of the cylinder

*/
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		*dist_oc;
	t_vector		*sphere_origin;
	t_pair_float	t;

	dist_oc = sub_vector(ray->origin, &csg->l->pos);
	sphere_origin = add_vector(&csg->l->pos, &obj->pos);
	if (!quadratic_solver(&t, dist_oc, ray->direction, csg->l->shape.cylinder.rad))
		return (our_free(dist_oc), our_free(sphere_origin), NULL);
	our_free(dist_oc);
	our_free(sphere_origin);
	if (t.t1 < 0 || (t.t2 < t.t1 && t.t2 > 0))
		return (new_collision(obj, csg, ray, t.t2));
	return (new_collision(obj, csg, ray, t.t1));
}
