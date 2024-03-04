/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/03/04 14:17:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Args:
	params: Array of strings containing the parameters of the object
*/
t_csg	*pr_new_plane(char *color)
{
	t_csg	*plane;

	plane = our_malloc(sizeof(t_csg));
	plane->type = LEAVE;
	plane->l = our_malloc(sizeof(t_csg_leave));
	plane->l->type = PLANE;
	//planes are never relative to the object
	plane->l->pos = (t_vector){0, 0, 0};
	plane->l->ort = (t_vector){0, 0, 0};
	parse_rgb(&plane->l->rgb, color);
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
	t_vector	*origin;
	float		ray_axis_dot_pl_axis;
	float		t;

	vector_normalizer(ray->direction);
	ray_axis_dot_pl_axis = vec_dot_product(ray->direction, &obj->ort);
	// Ray is parallel to the plane
	if (ray_axis_dot_pl_axis == 1)
	{
		printf("Ray is parallel to the plane\n");
		return (NULL);
	}
	// Ray is perpendicular to the plane, special case because of division by 0
	if (ray_axis_dot_pl_axis == 0)
	{
		origin = sub_vector(&obj->pos, ray->origin);
		// Not origin, but same variable to save memory
		t = vector_length(origin);
		our_free(origin);
		return (new_collision(obj, csg, ray, t));
	}
	// Any other angle
	origin = sub_vector(ray->origin, &obj->pos); // Substract with the plane origin
	t = -vec_dot_product(origin, &obj->ort) / ray_axis_dot_pl_axis;
	our_free(origin);
	// if (t > 0)
		return (new_collision(obj, csg, ray, t));
	printf("Plane: t is negative\n");
	return (NULL);
}
