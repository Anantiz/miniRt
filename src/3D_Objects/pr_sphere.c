/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/26 15:12:11 by aurban           ###   ########.fr       */
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
	params[0] = diameter
	params[1] = color
	(optional)params[2] = position
*/
t_csg	*pr_new_sphere(char **params)
{
	t_csg		*sphere;

	sphere = our_malloc(sizeof(t_csg));
	sphere->type = LEAVE;
	sphere->l = our_malloc(sizeof(t_csg_leave));
	sphere->l->type = SPHERE;
	sphere->l->ort = (t_vector){0, 0, 0};
	sphere->l->shape.sphere.rad = parse_float(params[0]) / 2;
	parse_rgb(&sphere->l->rgb, params[1]);
	if (params[2])
		parse_position(&sphere->l->pos, params[2]);
	else
		sphere->l->pos = (t_vector){0, 0, 0};
	return (sphere);
}

/*
Aint't that beautiful? (joke it's scary), quadratic formula + polynomial conversion

a=Dx2​+Dy2​+Dz2​

b=2×(Dx×(Ox−Cx)+Dy×(Oy−Cy)+Dz×(Oz−Cz))b=2×(Dx​×(Ox​−Cx​)+Dy​×(Oy​−Cy​)+Dz​×(Oz​−Cz​))

c=(Ox−Cx)2+(Oy−Cy)2+(Oz−Cz)2−R2c=(Ox​−Cx​)2+(Oy​−Cy​)2+(Oz​−Cz​)2−R2

I made a crime to fix an unknown bug:
	We do not inverse the sign of b during the equation, otherwise
	it gets the vector in the wrong direction, like why?

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
