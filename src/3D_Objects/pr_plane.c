/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
/*   Updated: 2024/03/06 20:53:35 by aurban           ###   ########.fr       */
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
#define PRINT_SAMPLE 10000
extern int has_printed;
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
	// We are litera-ly on the plane
	if (nominator == 0)
	{
		// if (has_printed % PRINT_SAMPLE == 0)
		// 	printf("nominator == 0\n"); has_printed;
		return (new_collision(obj, csg, ray, 0));
	}
	denominator = -vec_dot_product(ray->dir, csg->l->shape.plane.norm);
	// We are perpendicular to the normal thus parallel to the plane
	if (denominator == 0)
	{
		// if (has_printed % PRINT_SAMPLE == 0)
		// 	printf("denominator == 0\n"); has_printed;
		return (NULL);
	}
	t = nominator / denominator;
	if (t < 0)
	{
		// if (has_printed % PRINT_SAMPLE == 0)
		// 	printf("t < 0, nominator= %f,  denominator= %f\n",nominator , denominator ); has_printed;
		return (NULL);
	}
	// if (has_printed % PRINT_SAMPLE == 0)
		// printf("Plane t = %f, nominator= %f,  denominator= %f\n", t,nominator , denominator); has_printed;
	return (new_collision(obj, csg, ray, t));
}
