/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/06 22:07:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
If params len is not 5, segfault, please give me the right params
	params[0] = diameter
	params[1] = height
	params[2] = color
	(optional)params[3] = pos, else NULL
	(optional)[4] = orientation, else NULL
*/
t_csg	*pr_new_cylinder(char **params) // REDO THE PARSING
{
	t_csg	*cylinder;

	// Should not happen regardless of the input file.
	// (obj_cylinder should normally handle this)
	if (ft_strslen(params) < 3)
		error_exit("Cylinder: wrong number of parameters");
	cylinder = our_malloc(sizeof(t_csg));
	cylinder->type = LEAVE;
	cylinder->l = our_malloc(sizeof(t_object));
	cylinder->l->type = CYLINDER;
	cylinder->l->shape.cylinder.rad = ft_atoldb(params[0]) / 2;
	cylinder->l->shape.cylinder.height = ft_atoldb(params[1]);
	parse_rgb(&cylinder->l->rgb, params[2]);
	if (params[3])
		parse_position(&cylinder->l->pos, params[3]);
	else
		cylinder->l->pos = (t_vector){0, 0, 0};
	if (params[4])
		parse_orientation(&cylinder->l->dir, params[4]);
	else
		cylinder->l->dir = (t_vector){0, 0, 0};
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
	float			circle_radius = csg->l->shape.cylinder.rad;
	t_vector		*circle_center = &obj->pos; // Base of the cylinder
	float			angle;
	t_pair_float	semi_axis;

// Step 2, ROTATE THE CIRCLE
	//step 2.1: Measure the angle between the cylinder's axis and the z axis (our reference)
	angle = vec_dot_product(&(t_vector){0, 0, 1}, &obj->dir); // To be sure, I have to check if given a cylinder oriented in the z axis, the result is 0, but it should be
	//step 2.2: Create the ellipse using this angle
	semi_axis = (t_pair_float){circle_radius * cosf(angle), circle_radius * sinf(angle)};
/*Step 3: Check 2D collision with the ellipse
	Formula is (rx * t + ro_x - eo_x)^2 / a^2 + (ry * t + ro_y - eo_y)^2 / b^2 = 1
	Where rx, ry are the ray's direction, ro_x, ro_y are the ray's origin, eo_x,
	eo_y are the ellipse's origin, a, b are the ellipse's semi axis
*/
	// Will be written more concisely later, I'm just trying to understand the formula
	float	t = 0;
	float	a_sqrd = semi_axis.t1 * semi_axis.t1;
	float	b_sqrd = semi_axis.t2 * semi_axis.t2;
	float	center_x = circle_center->x + ray->pos->x;
	float	center_y = circle_center->y + ray->pos->y;

	// Now solve the quadratic equation with doube variables, wahou !
	// To be figured out ...

	// if t is negative, the collision is behind the camera
	if (t < 0) // Kinda not true, because if we use the z axis as {0, 0, 1} or {0, 0, -1}, the result will be inversed, I think, I'm not sure, to recheck
		return (NULL);
// Step 4: Check if the collision is within the cylinder's height
	// Above the cylinder
	if (ray->pos->z + t * ray->dir->z > obj->pos.z + csg->l->shape.cylinder.height - EPSILON)
		return (NULL);
	// Below the cylinder
	if (ray->pos->z + t * ray->dir->z < obj->pos.z + EPSILON)
		return (NULL);
	return (new_collision(obj, csg, ray, t));
}

/*

((ray_origin_x * t + ray_dir_x - ellipse_center)^2) / ellipse_radius_x^2 + ((ray_origin_y * t + ellipse_center + ray_dir_y)^2) / ellipseradius_y^2 = 1

1 -((t² + 2t)/a²) - ((t² + 2t)/b²) = (rx² + 2rx + 2cx + cx²)/a² + (ry² + 2ry + 2cy + cy²)/b²


...............................................................................
GPT Copy/Paste: the squared terms are written buggy as t2 instead of t^2
With cx being the origin x of the ray minus the center x of the ellipse and the same for cy
	Starting with your expanded equation:

	1−t2+2ta2−t2+2tb2=(rx2+2rx+2cx+cx2)a2+(ry2+2ry+2cy+cy2)b21−a2t2+2t​−b2t2+2t​=a2(rx2+2rx+2cx+cx2)​+b2(ry2+2ry+2cy+cy2)​

	Rearrange the terms:

	1−t2+2ta2−t2+2tb2−(rx2+2rx+2cx+cx2)a2−(ry2+2ry+2cy+cy2)b2=01−a2t2+2t​−b2t2+2t​−a2(rx2+2rx+2cx+cx2)​−b2(ry2+2ry+2cy+cy2)​=0

	Now, combine similar terms and rewrite it in the standard form:

	(−1a2−1b2)t2+(−2a2−2b2)t+(rx2+2rx+2cx+cx2)a2+(ry2+2ry+2cy+cy2)b2−1=0(−a21​−b21​)t2+(−a22​−b22​)t+a2(rx2+2rx+2cx+cx2)​+b2(ry2+2ry+2cy+cy2)​−1=0

	This is now a quadratic equation in the form at2+bt+c=0at2+bt+c=0, where:

	a=−1a2−1b2a=−a21​−b21​
	b=−2a2−2b2b=−a22​−b22​
	c=(rx2+2rx+2cx+cx2)a2+(ry2+2ry+2cy+cy2)b2−1c=a2(rx2+2rx+2cx+cx2)​+b2(ry2+2ry+2cy+cy2)​−1

	Now, you can use the quadratic formula to solve for tt:

	t=−b±b2−4ac2at=2a−b±b2−4ac
...............................................................................
​​

*/