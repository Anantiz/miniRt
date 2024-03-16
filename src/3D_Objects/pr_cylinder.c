/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/16 12:33:25 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Since all calls to this function are made by the parser, we don't need to check
the parameters, they are guaranteed to be either correct or a string placeholder

	Params:
		0: pos
		1: orientation
		2: diameter
		3: height
		4: color
*/
t_csg	*pr_new_cylinder(char **params) // REDO THE PARSING
{
	t_csg	*cylinder;

	cylinder = our_malloc(sizeof(t_csg));
	cylinder->type = LEAVE;
	cylinder->l = our_malloc(sizeof(t_leave));
	cylinder->l->type = CYLINDER;
	parse_position(&cylinder->l->pos, params[0]);
	parse_orientation_private(&cylinder->l->dir, params[1]);
	cylinder->l->shape.cylinder.rad = parse_float(params[2]) / 2;
	cylinder->l->shape.cylinder.height = parse_float(params[3]);
	parse_rgb(&cylinder->l->rgb, params[4]);
	return (cylinder);
}

/*
	Given the ray and cylinder pos+axis, find when the ray enters and exits
	the cylinder's height bounds

	(extract_height) == projection: gotta find a way to measure the "height" of
	a point along the cylinder axis

	Simplify the equation:
		magnitude(projection(ray_dir * t, cy_dir))
			<= magnitude (cy_pos + cy_dir * h - ray_pos)

		t = (magnitude (cy_pos + cy_dir * h - ray_pos)
			/ magnitude(cy_dir)) / dot(ray_dir, cy_dir)

	Solve for t and return the tuple
*/
t_pair_float	*height_inequality(t_ray *ray, t_vector *cy_p, t_vector *cy_d, float h)
{
	t_pair_float	*ret;
	t_vector		*tmp;
	float			cached[2];
	// We consider the cylinder's top as a vector from the origin instead of a point

	ret = our_malloc(sizeof(t_pair_float));
	cached[0] = vec_len(cy_d);
	cached[1] = vec_dot_product(ray->dir, cy_d);
	tmp = vec_cpy(cy_p);
	vec_sub_inplace(tmp, ray->pos);

	// Get t for Height exit
	ret->t2 = vec_len(tmp) / cached[0] / cached[1];

	// Get t for Height entry
	vec_add_inplace(tmp, vec_mult(h, cy_d));
	ret->t1 = vec_len(tmp) / cached[0] / cached[1];
	our_free(tmp);
	if (ret->t1 < 0 && ret->t2 < 0) // Behind the ray, early exit
		return (our_free(ret), NULL);
	return (ret);
}

/*
	When does the ray enter and exit the cylinder's radius
	Same as for the height, but this time we project the ray on the plane
*/
t_pair_float	*radius_inequality(t_ray *ray, t_vector *cy_p, t_vector *cy_d, float r)
{
	t_vector		*cy_plane;
	t_vector		*proj_ray_dir;
	t_vector		*proj_ray_pos;
	t_pair_float	*ret;
	float			dist;

	ret = our_malloc(sizeof(t_pair_float));
	// First get the cylinder's plane (orthogonal to the axis)
	cy_plane = get_orthogonal(cy_d);
	// Now project the ray on the plane
	proj_ray_dir = vec_project(ray->dir, cy_plane);
	proj_ray_pos = vec_project(ray->pos, cy_plane);

	// Now solve the inequation for t:
	/*
		Ray_p = proj_ray_pos + proj_ray_dir * t

		signed_dist(cy_p, Ray_p) <= r
		&&
		signed_dist(cy_p, Ray_p) >= -r
	*/


	if (dist < r) // Inside the cylinder
	{
		ret->t1 = 0;
		ret->t2 = INFINITY;
		return (ret);
	}
	return (ret);
}

static float	closest_overlap(t_pair_float *h, t_pair_float *r)
{
	// First check if the inequalities overlap
	/*
		So: if you enter and exit the cylinder's height before entering the radius
			it's not a valid overlap
		Same:
			if You enter and exit the radius before entering the height
			Not valid
	*/
	if (h->t1 < r->t1 && h->t2 < r->t1) // Height is before radius
		return (-1);
	if (r->t1 < h->t1 && r->t2 < h->t1) // Radius is before height
		return (-1);

	// Now get the moment where you enter the overlap
	// The furthest entry, in-between height and radius
	return (fmax(h->t1, r->t1));
}

/*
	1. Get an orthogonal plan to the cylinder's axis
	2. Solve the ray-plane intersection
		2.1 Reject negative values
	3. Check if it's in the radius and the height
*/
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_pair_float	*height_check;
	t_pair_float	*radius_check;
	float			t_cylinder;

	t_vector		*plane_intersect;
	float			t_plane;

	t_vector		*cy_axis;
	t_vector		*cy_origin;
	float			h;

	cy_origin = vec_add(&obj->pos, &csg->l->pos);
	cy_axis = vec_add(&obj->dir, &csg->l->dir);
	h = csg->l->shape.cylinder.height;

	// The cylinder axis is the normal of the plane
		// Deprecated
			// t_plane = plane_intersection(cy_origin, cy_axis, ray);
			// if (t_plane < 0)
			// 	return (free2(cy_origin, cy_axis), NULL);
			// plane_intersect = vec_mult(t_plane, ray->dir);
			// vec_realloc(&plane_intersect, vec_add(plane_intersect, ray->pos));
			// Now we have a plane intersect.
			// We need to check if it's in the height and radius at the same time
			// (It can be in the radius but not in the height, and vice versa)

	// Double inequality incoming:
	// Find when the ray reaches both the radius and the height
	// If there is no solution, the ray doesn't hit the cylinder
	// t_cylinder will be the result of the equation
	/*
		Goes like this:
			//Height inequality, gives a tuple of 2 values where the ray enters and exits the cylinder height
			Height_check(t_plane, cy_origin, cy_axis, ray)
			and
			//Radius inequality, gives a tuple of 2 values where the ray enters and exits the cylinder radius (Handle collinear case)
	*/

	// Less chance to be in the radius than in the height, so do radius first
	// to exit early
	radius_check = radius_inequality(ray, cy_origin, cy_axis, csg->l->shape.cylinder.rad);
	if (!radius_check)
		return (free3(cy_origin, cy_axis, radius_check), NULL);

	height_check = height_inequality(ray, cy_origin, cy_axis, h);
	if (!height_check)
		return (free4(cy_origin, cy_axis, radius_check, height_check), NULL);

	// Now get the overlap of the two inequalities and find the closest bound
	t_cylinder = closest_overlap(height_check, radius_check);
	free4(cy_origin, cy_axis, radius_check, height_check);
	if (t_cylinder < 0)
		return (NULL);
	return (new_collision(obj, csg, ray, t_cylinder));
}

/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*cy_data;
	t_vector	*tmp;

	(void)ray;
	/*
		To get the closest point on the axis, the idea is:
			Get a vector that is orthogonal to both the axis and the collision
			point, this vector will be the normal we want, make sure it's in the
			correct direction (point + normal = center_axis(at the same height))

		Since both the point and the axis are collinear, the cross product will
		give us a vector orthogonal to both, thus parallel to the cylinder's base
	*/
	cy_data = vec_add(&col->parent_obj->pos, &col->obj->l->pos);
	tmp = vec_sub(&col->point, cy_data);
	cy_data = vec_realloc(&cy_data, vec_add(&col->parent_obj->dir, &col->obj->l->dir));
	vec_normalize(cy_data);
	vec_normalize(tmp);
	// Maybe we should do smthing if it's on the side or the cap
	col->norm = vec_cross_product(tmp, cy_data);
	our_free(cy_data);
	vec_normalize(col->norm);
}
