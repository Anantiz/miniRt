/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 12:15:38 by aurban           ###   ########.fr       */
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
	float		nominator; // The relative origin of the ray to the plane
	float		denominator; // D⃗⋅A⃗
	float		t;

	nominator = vec_dot_product(&(t_vector){\
		ray->pos->x - obj->pos.x, \
		ray->pos->y - obj->pos.y, \
		ray->pos->z - obj->pos.z}, csg->l->shape.plane.norm);

	if (nominator == 0)
		return (new_collision(obj, csg, ray, 0));
	denominator = -vec_dot_product(ray->dir, csg->l->shape.plane.norm);
	if (denominator == 0) // Wtf ?? Past me, what did you do ? This is weird
		return (NULL);
	t = nominator / denominator;
	if (t < 0)
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
	col->norm = vec_cpy(col->obj->l->shape.plane.norm);
	// if (vec_dot_product(col->norm, ray->dir) > 0)
	// 	vec_negate(col->norm);
}
