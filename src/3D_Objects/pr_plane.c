/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:36 by aurban            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/24 22:16:10 by aurban           ###   ########.fr       */
=======
/*   Updated: 2024/03/25 10:44:33 by aurban           ###   ########.fr       */
>>>>>>> loris
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
	plane->type = LEAF;
	plane->l = our_malloc(sizeof(t_leaf));
	plane->l->type = PLANE;
	//planes are never relative to the object
	plane->l->pos = (t_vector){0, 0, 0};
	plane->l->dir = (t_vector){0, 0, 0};
	if (!parse_rgb(&plane->l->rgb, color))
		return (NULL);
	plane->l->reflect = 0;
	plane->l->refract = 0;
	return (plane);
}

double	plane_intersection(t_vector *plane_pos, t_vector *plane_norm, t_vector *ray_pos, t_vector *ray_dir)
{
	double		nominator; // The relative origin of the ray to the plane
	double		denominator; // D⃗⋅A⃗

	denominator = vec_dot_product(ray_dir, plane_norm);
	if (denominator == 0) // Ray is parallel to the plane because orthogonal to the normal
		return (-1);
	nominator = vec_dot_product(&(t_vector){\
		ray_pos->x - plane_pos->x, \
		ray_pos->y - plane_pos->y, \
		ray_pos->z - plane_pos->z}, plane_norm);
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
t_collision	*collider_plane(t_object *obj, t_leaf *csg, t_ray *ray)
{
	double		t;

	t = plane_intersection(&obj->pos, &csg->shape.plane.norm, ray->pos, ray->dir);
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
	col->norm = col->csg->shape.plane.norm;
	if (vec_dot_product(&col->norm, ray->dir) > 0)
		vec_negate(&col->norm);
	vec_normalize(&col->norm);
}
