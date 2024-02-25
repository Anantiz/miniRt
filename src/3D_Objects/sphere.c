/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 01:58:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 16:50:45 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"


/*
Aint't that beautiful? (joke it's scary)

a=Dx2​+Dy2​+Dz2​

b=2×(Dx×(Ox−Cx)+Dy×(Oy−Cy)+Dz×(Oz−Cz))b=2×(Dx​×(Ox​−Cx​)+Dy​×(Oy​−Cy​)+Dz​×(Oz​−Cz​))

c=(Ox−Cx)2+(Oy−Cy)2+(Oz−Cz)2−R2c=(Ox​−Cx​)2+(Oy​−Cy​)2+(Oz​−Cz​)2−R2

*/
t_csg	*new_sphere(char **params)
{
	t_csg		*sphere;

	if (ft_tablen(params) != 2)
		error_exit("Error: Sphere: wrong number of parameters");
	sphere = our_malloc(sizeof(t_csg));
	sphere->type = LEAVE;
	sphere->l = our_malloc(sizeof(t_csg_leave));
	sphere->l->type = SPHERE;
	sphere->l->ort = (t_vector){0, 0, 0};
	sphere->l->pos = (t_vector){0, 0, 0};
	sphere->l->shape.sphere.rad = parse_float(params[0]);
	parse_rgb(&sphere->l->color, params[1]);
	return (sphere);
}

bool	collider_sphere_quadratic(t_csg *csg, t_ray *ray, t_vector *dist_oc, \
t_pair_float *t)
{
	float		a;
	float		b;
	float		c;
	float		discriminant;

	a = vec_dot_product(ray->direction, ray->direction);
	if (a == 0)
		return (false);
	b = 2.0 * vec_dot_product(dist_oc, ray->direction);
	c = vec_dot_product(dist_oc, dist_oc);
	c -= (csg->l->shape.sphere.rad * csg->l->shape.sphere.rad);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t->t1 = (-b - sqrtf(discriminant)) / (2.0 * a);
	t->t2 = (-b + sqrtf(discriminant)) / (2.0 * a);
	if (t->t1 > 0 || t->t2 > 0)
		return (true);
	return (false);
}

t_collision	*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		*dist_oc;
	t_vector		*sphere_origin;
	t_pair_float	t;
	bool			ret;

	sphere_origin = add_vector(&obj->pos, &csg->l->pos);
	dist_oc = sub_vector(sphere_origin ,ray->origin);
	our_free(sphere_origin);
	ret = collider_sphere_quadratic(csg, ray, dist_oc, &t);
	our_free(dist_oc);
	if (!ret)
		return (NULL);
	if (t.t1 < 0 || (t.t2 < t.t1 && t.t2 > 0))
		return (new_collision(obj, csg, ray, t.t2));
	return (new_collision(obj, csg, ray, t.t1));
}
