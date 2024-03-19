/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_2D_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:33:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 15:26:57 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
	Return the closest intersection for the given ray, with a circle of radius r
	with the center at the origin
	(2D-Collision)
	Ray-Circle intersection:
		((ray_dir.x * t) - ray_pos)² + ((ray_dir.y * t) - ray_pos)² = r²
*/
double	cy_circle_intersection(t_vector *ray_pos, t_vector *ray_dir, double r)
{
	t_pair_double	t;
	double			a;
	double			b;
	double			c;

	a = ray_dir->x * ray_dir->x + ray_dir->y * ray_dir->y;
	b = 2 * (ray_dir->x * ray_pos->x + ray_dir->y * ray_pos->y);
	c = ray_pos->x * ray_pos->x + ray_pos->y * ray_pos->y - r * r;
	if (!quadratic_solver(a, b, c, &t))
		return (-INFINITY);
	return (smallest_pos(t.t1, t.t2));
}

double	cy_cap_intersection(t_vector *ray_pos, t_vector *ray_dir, double r, double h)
{
	double		t1;
	double		t2;
	double		r_sqrd;

	r_sqrd = r * r;
	// Check height intersection
	t1 = (0 - ray_pos->z) / ray_dir->z;
	t2 = (h - ray_pos->z) / ray_dir->z;
	// Now check if the ray is inside the circle, otherwise, it's not a collision
	if ((ray_dir->x * t1 + ray_pos->x) * (ray_dir->x * t1 + ray_pos->x) \
		+ (ray_dir->y * t1 + ray_pos->y) * (ray_dir->y * t1 + ray_pos->y) > r_sqrd)
		t1 = -INFINITY;
	if ((ray_dir->x * t2 + ray_pos->x) * (ray_dir->x * t2 + ray_pos->x) \
		+ (ray_dir->y * t2 + ray_pos->y) * (ray_dir->y * t2 + ray_pos->y) > r_sqrd)
		t2 = -INFINITY;
	return (smallest_pos(t1, t2));
}
