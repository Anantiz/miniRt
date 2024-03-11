/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 12:10:05 by aurban           ###   ########.fr       */
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
Step 1: Create A circle

Step 2, ROTATE THE CIRCLE
	step 2.1: Measure the angle between the cylinder's axis and the z axis (our reference)
	step 2.2: Create the ellipse using this angle

Step 3: Check 2D collision with the ellipse
Step 4: Check if the collision is within the cylinder's height
*/
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	/*
		Issues to fix:
		When the circle is rotated, the ray.dir should be affected by the rotation
		too, TO DO NEXT TIME
	*/
	t_pair_float	sr;
	t_vector		*v;
	float			angle;

	// Step 1 && 2
	v = vec_add(&csg->l->dir, &obj->dir); // V is the cylinder Axis
	vec_normalize(v);
	angle = vec2d_get_angle_rad(v, &(t_vector){0, 0, 1});
	if(angle)
		rotate_circle(csg->l->shape.cylinder.rad, &sr, 1 - angle);
	else
		sr = (t_pair_float){csg->l->shape.cylinder.rad, csg->l->shape.cylinder.rad};
	our_free(v);
	v = vec_add(&csg->l->pos, &obj->pos); // V is the cylinder center

	// Step 3
	if (!ellipse_intersection(&sr, v, ray))
		return (our_free(v), NULL);

	// Step 4
	// For some reason, the t1 and t2 are inverted I don't know why, but it works like that don't touch it
	if (sr.t1 > 0 && (ray->pos->z + ray->dir->z * sr.t1) < v->z + csg->l->shape.cylinder.height && sr.t1 < sr.t2)
		return (our_free(v), new_collision(obj, csg, ray, sr.t2));
	else if (sr.t2 > 0 && (ray->pos->z + ray->dir->z * sr.t2) < v->z + csg->l->shape.cylinder.height)
		return (our_free(v), new_collision(obj, csg, ray, sr.t1));
	return (our_free(v), NULL);
}

/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*norm;
	t_vector	*tmp;

	tmp = vec_add(&col->parent_obj->pos, &col->obj->l->pos);
	norm = vec_sub(&col->point, tmp);
	norm->z -= col->dist * (ray->dir->z);
	vec_normalize(norm);
	col->norm = norm;
	our_free(tmp);
}
