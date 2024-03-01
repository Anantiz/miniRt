/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 12:40:06 by aurban           ###   ########.fr       */
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
	sphere->l = our_malloc(sizeof(t_csg_leave));
	sphere->l->type = SPHERE;
	sphere->l->ort = (t_vector){0, 0, 0};
	parse_position(&sphere->l->pos, params[0]);
	sphere->l->shape.sphere.rad = parse_float(params[1]) / 2;
	parse_rgb(&sphere->l->rgb, params[2]);
	return (sphere);
}

/*
quadratic formula + polynomial conversion

a=Dx2​+Dy2​+Dz2​

b=2×(Dx×(Ox−Cx)+Dy×(Oy−Cy)+Dz×(Oz−Cz))b=2×(Dx​×(Ox​−Cx​)+Dy​×(Oy​−Cy​)+Dz​×(Oz​−Cz​))

c=(Ox−Cx)2+(Oy−Cy)2+(Oz−Cz)2−R2c=(Ox​−Cx​)2+(Oy​−Cy​)2+(Oz​−Cz​)2−R2

*/
t_collision	*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		*dist_oc;
	t_vector		*sphere_origin;
	t_pair_float	t;
	bool			ret;

	sphere_origin = add_vector(&obj->pos, &csg->l->pos);
	dist_oc = sub_vector(sphere_origin, ray->origin);
	our_free(sphere_origin);
	ret = quadratic_solver(&t, dist_oc, ray->direction, csg->l->shape.sphere.rad);
	our_free(dist_oc);
	if (!ret)
		return (NULL);
	if (t.t1 < 0 || (t.t2 < t.t1 && t.t2 > 0))
		return (new_collision(obj, csg, ray, t.t2));
	return (new_collision(obj, csg, ray, t.t1));
}
