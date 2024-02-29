/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/02/29 14:49:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Args:
	params: Array of strings containing the parameters of the object
*/
t_csg	*pr_new_plane(char **params)
{
	t_csg	*plane;

	if (ft_tablen(params) != 3)
		error_exit("Wrong parameters count : Plane : pr_new_");
	plane = our_malloc(sizeof(t_csg));
	plane->type = LEAVE;
	plane->l = our_malloc(sizeof(t_object));
	plane->l->type = PLANE;
	parse_position(&plane->l->pos, params[0]);
	parse_orientation(&plane->l->ort, params[1]);
	parse_rgb(&plane->l->rgb, params[2]);
	return (plane);
}

/*
	Plane equation:
  		(P⃗−C)⋅A⃗ = 0
	Ray equation:
		P⃗ = R⃗c + t⋅D⃗
	Solve plane equation for P as the ray.

If t is positive it's a hit, else it's a miss.
If the division by the dot product of the ray and the plane axis is 0, it's a miss.
(it's parallel to the plane, so it's not going to hit it).

*/
t_collision	*collider_plane(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector	*plane_axis;
	t_vector	*origin;
	float		ray_axis_dot_pl_axis;
	float		t;

	plane_axis = add_vector(&obj->pos, &csg->l->ort);
	ray_axis_dot_pl_axis = vec_dot_product(ray->direction, plane_axis);
	if (ray_axis_dot_pl_axis == 0)
		return (our_free(plane_axis), NULL);

	origin = add_vector(&obj->pos, &csg->l->pos);
	rea_v(&origin, add_vector(origin, ray->origin));

	t = -vec_dot_product(origin, plane_axis) /	ray_axis_dot_pl_axis;
	our_free(origin);
	our_free(plane_axis);
	if (t > 0)
		return (new_collision(obj, csg, ray, t));
	return (NULL);
}
