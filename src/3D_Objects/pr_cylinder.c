/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 16:21:20 by aurban           ###   ########.fr       */
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

static void	cy_get_theta(double theta[3], t_vector *cy_axis_a, t_vector *cy_axis_b)
{
	theta[0] = atan2(cy_axis_a->y + cy_axis_b->y, cy_axis_a->z + cy_axis_b->z);
	theta[1] = atan2(cy_axis_a->x + cy_axis_b->x, cy_axis_a->z + cy_axis_b->z);
	theta[2] = 0;//atan2(cy_axis_a->x + cy_axis_b->x, cy_axis_a->y + cy_axis_b->y);
}


/*
	Store the t of collision and the z(height) in t_col[0] and t_col[1]
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
	if (collision_z > h || collision_z < 0) // Out of heigh bounds
	{
		// Check if the other collision is in bounds
		//fmax is ok since the other is either Smaller and negative (so max will give the same as now)
		// or it is Positive and larger than the first t so it will give the larger value
		t_col[0] = fmax(t_col[0], t_col[1]);
		collision_z = pos->z + t_col[0] * rdir_l->z;
		t_col[1] = collision_z;
		if (collision_z > h + EPSILON || collision_z < -EPSILON)
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
	t_collision		*coll;
	t_vector		*rdir_l;
	t_vector		*pos[2]; // pos[1] is a temp, but coding norm abuse ;D
	double			theta[3];
	double			t_col[2];

	//Part 1: Convert to local coordinates
	pos[0] = vec_add(&obj->pos, &csg->pos);
	cy_get_theta(theta, &obj->dir, &csg->dir);
	rdir_l = vec_matrix_rotate(ray->dir, theta);
	pos[1] = vec_sub_inplace(vec_copy(ray->pos), pos[0]);
	pos[0] = vec_realloc(&pos, vec_matrix_rotate(pos[1], theta));
	t_col[0] = cy_circle_intersection(pos[0], rdir_l, \
		csg->shape.cylinder.rad);
	t_col[1] = cy_cap_intersection(pos[0], rdir_l, \
		csg->shape.cylinder.rad, csg->shape.cylinder.height);

	// Part 3: Get the closest collision
	if (!cy_get_t(t_col, pos, rdir_l, csg->shape.cylinder.height))
		return (free3(pos, rdir_l, pos[1]), NULL);

	coll = new_collision(obj, csg, ray, t_col[0]);
	return (free3(pos, rdir_l, pos[1]), coll);
}
/*
	Already done
*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	// If cap
	col->norm = vec_add(&col->csg->dir, &col->obj->dir);

	// Put the correct normal sign (Facing the ray), kinda a cheat, cuz if
	// You are
	if (vec_dot_product(col->norm, ray->dir) > 0)
		vec_negate(col->norm);
}
