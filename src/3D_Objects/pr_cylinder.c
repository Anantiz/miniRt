/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/07 14:30:04 by aurban           ###   ########.fr       */
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
Step 1: Create A circle
Step 2, ROTATE THE CIRCLE
	step 2.1: Measure the angle between the cylinder's axis and the z axis (our reference)
	step 2.2: Create the ellipse using this angle
Step 3: Check 2D collision with the ellipse
Step 4: Check if the collision is within the cylinder's height
*/
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
// Step 1: Create A circle
	float			angle;
	t_pair_float	semi_axis;
	// Shorthands for cleaner code
	float			circle_radius = csg->l->shape.cylinder.rad;
	t_vector		*circle_center = &obj->pos; // Base of the cylinder

// Step 2, ROTATE THE CIRCLE
	//step 2.1: Measure the angle between the cylinder's axis and the z axis (our reference)
	angle = vec_dot_product(&(t_vector){0, 0, 1}, &obj->dir); // To be sure, I have to check if given a cylinder oriented in the z axis, the result is 0, but it should be
	//step 2.2: Create the ellipse using this angle
	// angle = M_PI / 2; // For now, we'll just use a circle
	semi_axis = (t_pair_float){circle_radius * cosf(angle), circle_radius * sinf(angle)};


/*Step 3: Check 2D collision with the ellipse
	Formula is (rx * t + ro_x - eo_x)^2 / a^2 + (ry * t + ro_y - eo_y)^2 / b^2 = 1
	Where rx, ry are the ray's direction, ro_x, ro_y are the ray's origin, eo_x,
	eo_y are the ellipse's origin, a, b are the ellipse's semi axis
*/
	// Will be written more concisely later, I'm just trying to understand the formula
	// I actually will make it a whole function
	t_pair_float	t;

	// Ellipse equation terms
	float	a_sqrd = semi_axis.t1 * semi_axis.t1;
	float	b_sqrd = semi_axis.t2 * semi_axis.t2;
	float	c_x = circle_center->x + ray->pos->x;
	float	c_y = circle_center->y + ray->pos->y;
	t_vector	*dir = produit_vectoriel(&obj->dir, &(t_vector){0, 0, 1}); // No idea why, just trying things, it dosn't change anything anyway
	float	dir_x = dir->x;
	float	dir_y = dir->y;
	our_free(dir);
	// Quadratic equation terms
	float	a = (1 / a_sqrd) + (1 / b_sqrd);
	float	b = 2 * a;
		// C is a whole mess
	float	c = (((dir_x * dir_x) + (2 * dir_x * c_x) + (c_x * c_x)) / a_sqrd) \
				+ (((dir_y * dir_y) + (2 * dir_y * c_y) + (c_y * c_y)) / b_sqrd);
	// Solve the quadratic equation
	if (!quadratic_solver(a, b, c - 1, &t))
	{
		printf("No quadratic solution\n");
		// // Terms
		// printf("\tSemi axes: %f, %f\n", semi_axis.t1, semi_axis.t2);
		// printf("\tRadius: %f\n", circle_radius);
		// printf("\tSquared_terms: %f, %f\n", a_sqrd, b_sqrd);
		// printf("\tAngle: %f\n", angle);
		printf("\ta: %f\n", a);
		printf("\tb: %f\n", b);
		printf("\tc: %f\n", c);
		return (NULL);
	}

// Step 4: Check if the collision is within the cylinder's height

	// Checks for the intersection on our side of the cylinder
	float	closest_t;
	if (t.t1 < 0 || (t.t2 > 0 && t.t2 < t.t1))
		closest_t = t.t2;
	else
		closest_t = t.t1;

	// Above the cylinder
	if (ray->pos->z + closest_t * ray->dir->z > obj->pos.z + csg->l->shape.cylinder.height - EPSILON)
		return (NULL);
	// Below the cylinder
	if (ray->pos->z + closest_t * ray->dir->z < obj->pos.z + EPSILON)
		return (NULL);
	return (new_collision(obj, csg, ray, closest_t));
}

/*

((ray_origin_x * t + ray_dir_x - ellipse_center)^2) / ellipse_radius_x^2 + ((ray_origin_y * t + ellipse_center + ray_dir_y)^2) / ellipseradius_y^2 = 1

1 -((t² + 2t)/a²) - ((t² + 2t)/b²) = (rx² + 2rx + 2cx + cx²)/a² + (ry² + 2ry + 2cy + cy²)/b²


*/