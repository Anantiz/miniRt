/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/15 17:24:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
	Note for tommorow:

	The maths don't seemn to work, look at all of it again
	Then think about how dumb it might be, and correct it again.

	Then write it into code.

	I think the idea is to:
		- Create a circle, this is the cylinder front profile (I think it's okay)
		- Rotate the circle, if the cylinder is not seen from face
		it's technically just a rotated circle (I think this part looks okay too)

		- Then, we have to check the collision with the circle
			-Quadratic equation, I think the whole polynomial is wrong
			Idk how the f did I manage to have such a complicated equation
			cuz compared to others I've done this one has too many terms
			LOOK AT IT AGAIN
		Then finnaly, I think this one is okay tho, chek if it's in the cylinder's height

	Because I somehow managed to create a dam sem-parabola (one vertice
	is parabolique and the other is straight) instead of a cylinder
	How the f did I manage to do that ?   ??


	Mainly, What causes issue it the discrepancy between a and b that are relatively small
	and the c that is huge, my C is way too complexe, or the two others are too simple
	Probably both ... It's not tomorow that I'll get a phd in maths.
*/

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

	(extract_height): gotta find a way to measure the "height" of a point along the cylinder axis
	Simplify the equation:
		magnitude(projection(ray_dir * t, cy_dir)) <= magnitude (cy_pos + cy_dir * h - ray_pos)
		t = (magnitude (cy_pos + cy_dir * h - ray_pos) / magnitude(cy_dir)) / dot(ray_dir, cy_dir)
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
	if (ret->t1 < 0 && ret->t2 < 0)
		return (our_free(ret), NULL);
	return (ret);
}

/*
	When does the ray enter and exit the cylinder's radius
*/
t_pair_float	*radius_inequality(t_ray *ray, t_vector *cy_p, t_vector *cy_d, float r)
{
	t_pair_float	*ret;
	t_vector		*tmp;
	float			cached[2];


	ret = our_malloc(sizeof(t_pair_float));

	return (ret);
}


/*
	1. Get an orthogonal plan to the cylinder's axis
	2. Solve the ray-plane intersection
		2.1 Reject negative values
	3. Check if it's in the radius and the height
*/
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		*cy_axis;
	t_vector		*cy_origin;
	float			h;
	t_vector		*plane_intersect;
	float			intersect_dist;
	float			t_plane;
	float			t_cylinder;

	cy_origin = vec_add(&obj->pos, &csg->l->pos);
	cy_axis = vec_add(&obj->dir, &csg->l->dir);
	h = csg->l->shape.cylinder.height;

	// The cylinder axis is the normal of the plane
	t_plane = plane_intersection(cy_origin, cy_axis, ray);
	if (t_plane < 0)
		return (free2(cy_origin, cy_axis), NULL);
	plane_intersect = vec_mult(t_plane, ray->dir);
	vec_realloc(&plane_intersect, vec_add(plane_intersect, ray->pos));
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
	t_pair_float	*height_check;
	t_pair_float	*radius_check;
	height_check = height_inequality(ray, cy_origin, cy_axis, h);
	radius_check = radius_inequality(ray, cy_origin, cy_axis, csg->l->shape.cylinder.rad);
	// Check if the values exist
	if (!height_check || !radius_check)
		return (free4(cy_origin, cy_axis, radius_check, height_check), NULL);
	// Now get the overlap of the two inequalities and find the closest bound
	/*
		Hopefully that will work :D
	*/
	return (new_collision(obj, csg, ray, t_cylinder));
}

/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*center_axis;

	(void)ray;
	center_axis = vec_add(&col->parent_obj->pos, &col->obj->l->pos);
	// As compared to a sphere, we have to ignore the height, because
	// Cylinder's normals are only defined by the circle's normals
	center_axis->y = col->point.y; // Kinda wrong if the cylinder don't point up
	col->norm = vec_sub(&col->point, center_axis);
	our_free(center_axis);
	vec_normalize(col->norm );
}
