/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/03/16 14:36:05 by aurban           ###   ########.fr       */
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
	plane->l = our_malloc(sizeof(t_leave));
	plane->l->type = PLANE;
	//planes are never relative to the object
	plane->l->pos = (t_vector){0, 0, 0};
	plane->l->dir = (t_vector){0, 0, 0};
	parse_rgb(&plane->l->rgb, color);
	return (plane);
}

float	plane_intersection(t_vector *plane_pos, t_vector *plane_norm, t_ray *ray)
{
	float		nominator; // The relative origin of the ray to the plane
	float		denominator; // D⃗⋅A⃗

	denominator = vec_dot_product(ray->dir, plane_norm);
	if (fabs(denominator) < EPSILON) // Ray is parallel to the plane because orthogonal to the normal
		return (INFINITY);
	nominator = vec_dot_product(&(t_vector){\
		ray->pos->x - plane_pos->x, \
		ray->pos->y - plane_pos->y, \
		ray->pos->z - plane_pos->z}, plane_norm);
	return (-nominator / denominator);
}

/*
	Plane equation:
		(P⃗−C)⋅A⃗ = 0
	Ray equation:
		P⃗ = R⃗c + t⋅D⃗
	Solve plane equation for P as the ray.

	t = (C - R⃗c)⋅A⃗ / D⃗⋅A⃗
	With:
		A⃗ = csg->l->shape.plane.norm
		D⃗ = ray->dir
		(C - R⃗c)⋅A⃗ = nominator

	Return:
		Pointer to a collision struct if there is a collision
		NULL if no parallel or intersection is opposite to the ray direction
*/
t_collision	*collider_plane(t_object *obj, t_csg *csg, t_ray *ray)
{
	float		t;

	t = plane_intersection(&obj->pos, csg->l->shape.plane.norm, ray);
	if (t < 0 || t == INFINITY)
		return (NULL);
	return (new_collision(obj, csg, ray, t));
}

/*
	Plane normal is the plane normal
	(Surprising, I know)
*/
void	collider_plane_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	col->norm = vec_copy(col->obj->l->shape.plane.norm);
	// Because the normal direction don't matter for a plane
	if (vec_dot_product(col->norm, ray->dir) > 0) // Most probably useless tho
		vec_negate(col->norm);
}

/*

*/