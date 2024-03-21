/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/21 14:37:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

extern long my_x;
extern long my_y;
extern bool print_allow;
int	sample = 0;

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
t_csg	*pr_new_cylinder(char **params)
{
	t_csg	*cylinder;

	cylinder = our_malloc(sizeof(t_csg));
	cylinder->type = LEAVE;
	cylinder->l = our_malloc(sizeof(t_leave));
	cylinder->l->type = CYLINDER;
	parse_position(&cylinder->l->pos, params[0]);
	parse_orientation_private(&cylinder->l->dir, params[1]);
	cylinder->l->shape.cylinder.rad = parse_double(params[2]) / 2;
	cylinder->l->shape.cylinder.height = parse_double(params[3]);
	parse_rgb(&cylinder->l->rgb, params[4]);
	cylinder->l->reflect = 0;
	cylinder->l->refract = 0;
	return (cylinder);
}

/*
	Add the two given axis to get the cylinder's axis
*/
static void	cy_get_theta(double theta[3], t_vector *cy_axis)
{
	theta[0] = (M_PI / 2) - asin(cy_axis->z / sqrt(cy_axis->x * cy_axis->x + cy_axis->z * cy_axis->z));
	theta[1] = acos (cy_axis->z / sqrt(cy_axis->y * cy_axis->y + cy_axis->z * cy_axis->z));
	theta[2] = 0 ;
}

// Garbage, might reuse
	// // Version 1: Works for orientations along a single axis
	// theta[0] = atan2(cy_axis->y, cy_axis->z);

	// // Calculate the rotation angle around the y-axis
	// theta[1] = -atan2(cy_axis->x, sqrt(cy_axis->x * cy_axis->x + cy_axis->z * cy_axis->z));
	// theta[2] = 0;

	// // Absolute cheat, but it helps (still not perfect) -\_(x_x)_/-
	// if (theta[0] == 0 && theta[1] != 0)
	// {
	// 	// theta[1] *= 2;
	// }

/*
	Store the appropriate values in t_col[0]
	and the height of the collision in t_col[1]
*/
static bool	cy_get_t(double t_col[2], t_vector *pos, t_vector *rdir_l, double h)
{
	double	t;
	double	collision_z;

	// Get the closest collision that is non-negative
	t = smallest_pos(t_col[0], t_col[1]);
	if (t < 0) // Behind the camera
		return (false);
	collision_z = pos->z + t * rdir_l->z;
	if (collision_z > h || collision_z < -EPSILON) // Out of height bounds
	{
		// Check if the other collision is in bounds
		//fmax is ok since the other is either Smaller and negative (so max will give the same as now)
		// or it is Positive and larger than the first t so it will give the larger value
		t_col[0] = fmax(t_col[0], t_col[1]);
		collision_z = pos->z + t_col[0] * rdir_l->z;
		t_col[1] = collision_z;
		if (collision_z > h || collision_z < -EPSILON)
			return (false);
	}
	else
	{
		t_col[0] = t;
		t_col[1] = collision_z;
	}
	return (true);
}


/*
	1.Convert global coordinates to local coordinates
	The conversion will be transformation from:
		The given cylinder's axis to the z-axis
	2. Solve the equation for the cylinder
	3. Convert the result back to global coordinates
	Super ugly, but I've been working on this stupid cylinder for too long
	Screw cylinders, me and my homies hate cylinders

	Note:
		I'll code transfrormation matrices and conversions and all that stuff
		in here, Once that works I'll copy-paste the matrix-rotation part
		in it's own module
*/
t_collision			*collider_cylinder(t_object *obj, t_leave *csg, t_ray *ray)
{
	t_vector		*rdir_l;
	t_vector		*pos;
	t_vector		*tmp;
	double			theta[3];
	double			t_col[2];

	//Part 1: Convert to local coordinates
	pos = vec_add(&obj->pos, &csg->pos);
	cy_get_theta(theta, &(t_vector){obj->dir.x + csg->dir.x, obj->dir.y + csg->dir.y, obj->dir.z + csg->dir.z});
	rdir_l = vec_matrix_rotate(ray->dir, theta);
	vec_normalize(rdir_l);
	static int		once = 0;
	if (once < 6)
	{
		tmp = vec_add(&obj->dir, &csg->dir);
		printf("Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
		printf("Before rotation:\t");
		print_vector(tmp);
		tmp = vec_matrix_rotate(tmp, theta);
		printf("After rotation :\t");
		print_vector(tmp);
		printf("\n");
		once++;
	}
	tmp = vec_sub_inplace(vec_copy(ray->pos), pos);
	pos = vec_realloc(&pos, vec_matrix_rotate(tmp, theta));
	t_col[0] = cy_circle_intersection(pos, rdir_l, \
		csg->shape.cylinder.rad);
	t_col[1] = cy_cap_intersection(pos, rdir_l, \
		csg->shape.cylinder.rad, csg->shape.cylinder.height);

	// Part 3: Get the closest collision
	if (!cy_get_t(t_col, pos, rdir_l, csg->shape.cylinder.height))
		return (free3(pos, rdir_l, tmp), NULL);
	csg->shape.cylinder.z_impact = fabs(t_col[1]);
	return (free3(pos, rdir_l, tmp), new_collision(obj, csg, ray, t_col[0]));
}

void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*axis_ray_impact_plane;
	t_vector	*cy_axis;
	t_vector	*cy_pos;

	(void)ray;
	cy_axis = vec_add(&col->csg->dir, &col->obj->dir);
	cy_pos = vec_add(&col->csg->pos, &col->obj->pos);

	// Now the we have a point along the cylinder axis at the same height as
	// the collision
	vec_mult_inplace(col->csg->shape.cylinder.z_impact, cy_axis);
	// Add the position of the cylinder
	vec_add_inplace(cy_pos, cy_axis);

	// Susbtract the collision point to get the axis_ray_impact_plane
	//(the normal)
	axis_ray_impact_plane = vec_sub(&col->point, cy_pos);
	vec_normalize(axis_ray_impact_plane);

	if (vec_dist(&col->point, cy_pos) < col->csg->shape.cylinder.rad - EPSILON) // Cap
		col->norm = vec_add(&col->csg->dir, &col->obj->dir);
	else // Tube
		col->norm = axis_ray_impact_plane;
	free2(cy_axis, cy_pos);
}
