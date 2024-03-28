/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/28 12:34:32 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

extern long my_x;
extern long my_y;
extern bool print_allow;
int	sample = 0;

#define INTER_CAP_SIDE 1
#define INTER_CIRCLE_SIDE -1

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
t_csg	*pr_new_cylinder(t_vector coordinates[2], char **params)
{
	t_csg	*cy;

	cy = our_malloc(sizeof(t_csg));
	cy->type = LEAF;
	cy->l = our_malloc(sizeof(t_leaf));
	cy->l->type = CYLINDER;
	cy->l->pos = coordinates[0];
	cy->l->dir = coordinates[1];
	if (!parse_double(params[0], &cy->l->shape.cylinder.r))
		return (NULL);
	cy->l->shape.cylinder.r /= 2;
	if (!parse_double(params[1], &cy->l->shape.cylinder.h))
		return (NULL);
	cy->l->shape.cylinder.r2 = pow(cy->l->shape.cylinder.r, 2);
	if (!parse_rgb(&cy->l->rgb, params[2]))
		return (NULL);
	cy->l->reflect = 1.5;
	cy->l->refract = 0;
	return (cy);
}

/*
	Store the appropriate values in t_col[0]
	and the height of the collision in t_col[1]
*/
static bool	cy_get_t(double t_col[2], t_vector *ray_pos_l, t_vector *rdir_l, double h)
{
	double	t;
	double	collision_z;

	// Get the closest collision that is non-negative
	t = smallest_pos(t_col[0], t_col[1]);
	if (t < 0) // Behind the camera
		return (false);
	collision_z = ray_pos_l->z + t * rdir_l->z;
	if (collision_z > h || collision_z < -EPSILON) // Out of height bounds
	{
		// Check if the other collision is in bounds
		//fmax is ok since the other is either Smaller and negative (so max will give the same as now)
		// or it is Positive and larger than the first t so it will give the larger value
		t_col[0] = fmax(t_col[0], t_col[1]);
		collision_z = ray_pos_l->z + t_col[0] * rdir_l->z;
		if (collision_z > h || collision_z < -EPSILON)
			return (false);
	}
	else
		t_col[0] = t;

	// For the norm
	if (t_col[0] == t_col[1])
		t_col[1] = INTER_CAP_SIDE;
	else
		t_col[1] = INTER_CIRCLE_SIDE;
	return (true);
}

/*
ray_l[0] = pos
ray_l[1] = dir
*/
inline t_vector	cy_get_norm(t_collision *col, t_vector *ray_l[2], \
double theta[3], int type)
{
	t_vector	ret;

	if (type == INTER_CAP_SIDE)
		return (col->csg->dir);
	ret = vmult(ray_l[1], col->t);
	vec_add_inplace(&ret, ray_l[0]);
	ret = (t_vector){ret.x, ret.y, 0};
	ret = mtx_rotate_y(&ret, -theta[1]);
	ret = mtx_rotate_x(&ret, -theta[0]);
	vec_normalize(&ret);
	return (ret);
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
t_collision			*collider_cylinder(t_object *obj, t_leaf *csg, t_ray *ray)
{
	// static int		once = 0;

	static double	theta[3];
	t_collision		*col;
	t_vector		ray_dir_l;
	t_vector		ray_pos_l;
	double			t_col[2];

	// Get the angles to rotate the cylinder to the z-axis
	t_vector	tmp;
	tmp = csg->dir;
	theta[0] = atan2(tmp.y, tmp.z);
	tmp = mtx_rotate_x(&tmp, theta[0]);
	theta[1] = -atan2(tmp.x, tmp.z);
	tmp = mtx_rotate_y(&tmp, theta[1]);
	// Now we have the angles to rotate the cylinder to the z-axis

	ray_dir_l = mtx_rotate_x(ray->dir, theta[0]);
	ray_dir_l = mtx_rotate_y(&ray_dir_l, theta[1]);

	ray_pos_l = vsub(ray->pos, &csg->pos);
	ray_pos_l = mtx_rotate_x(&ray_pos_l, theta[0]);
	ray_pos_l = mtx_rotate_y(&ray_pos_l, theta[1]);

	t_col[0] = cy_circle_intersection(&ray_pos_l, &ray_dir_l, \
		csg->shape.cylinder.r2);
	t_col[1] = cy_cap_intersection(&ray_pos_l, &ray_dir_l, \
		csg->shape.cylinder.r2, csg->shape.cylinder.h);

	// Part 3: Get the closest collision
	if (!cy_get_t(t_col, &ray_pos_l, &ray_dir_l, csg->shape.cylinder.h))
		return (NULL);
	col = new_collision(obj, csg, ray, t_col[0]);
	col->norm = cy_get_norm(col, (t_vector*[2]){&ray_pos_l, &ray_dir_l}, theta, t_col[1]);
	return (col);
}


// OBSOLETE, but required because invoked by new_collision
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	(void)col;
}
