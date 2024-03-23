/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/23 21:35:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

extern long my_x;
extern long my_y;
extern bool print_allow;
int	sample = 0;

#define INTER_CAP_SIDE 1
#define INTER_CIRLCE_SIDE -1

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
	t_csg	*cy;

	cy = our_malloc(sizeof(t_csg));
	cy->type = LEAVE;
	cy->l = our_malloc(sizeof(t_leave));
	cy->l->type = CYLINDER;
	parse_position(&cy->l->pos, params[0]);
	parse_orientation_private(&cy->l->dir, params[1]);
	cy->l->shape.cylinder.r = parse_double(params[2]) / 2;
	cy->l->shape.cylinder.h = parse_double(params[3]);
	cy->l->shape.cylinder.r2 = cy->l->shape.cylinder.r \
	* cy->l->shape.cylinder.r;
	parse_rgb(&cy->l->rgb, params[4]);
	cy->l->reflect = 0;
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
		t_col[1] = INTER_CIRLCE_SIDE;
	return (true);
}

/*
ray_l[0] = pos
ray_l[1] = dir
*/
inline t_vector	*cy_get_norm(t_collision *col, t_vector *ray_l[2], \
double theta[3], double theta_b[3], int type)
{
	t_vector	temp;
	(void)theta_b;

	if (type == INTER_CAP_SIDE)
		return (vec_copy(&col->csg->dir));
	temp = (t_vector){ray_l[0]->x + ray_l[1]->x * col->t, ray_l[0]->y + ray_l[1]->y * col->t, col->t};
	return (vec_matrix_rev_rotate(&temp, theta));
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
	static int		once = 0;

	double			theta[3];
	t_collision		*col;
	t_vector		*ray_dir_l;
	t_vector		*ray_pos_l;
	double			t_col[2];

	//Part 1: Convert to local coordinates
	absolute_cheat(&csg->dir, theta);


	if (once < 6)
	{
		t_vector	*tmp;

		printf("Test %d:\n", once + 1);
		printf("1-Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
		printf("\t1-Before rotation:\t");
		print_vector(&csg->dir);
		printf("\t1-After rotation :\t");
		tmp = vec_matrix_rotate(&csg->dir, theta);
		vec_normalize(tmp);
		print_vector(tmp);

		our_free(tmp);
		printf("\n");

		printf("\n");
		once++;
	}
	ray_dir_l = vec_matrix_rotate(ray->dir, theta);

	ray_pos_l = vec_sub(ray->pos, &csg->pos);
	vec_realloc(&ray_pos_l, vec_matrix_rotate(ray_pos_l, theta));

	t_col[0] = cy_circle_intersection(ray_pos_l, ray_dir_l, \
		csg->shape.cylinder.r2);
	t_col[1] = cy_cap_intersection(ray_pos_l, ray_dir_l, \
		csg->shape.cylinder.r2, csg->shape.cylinder.h);

	// Part 3: Get the closest collision
	if (!cy_get_t(t_col, ray_pos_l, ray_dir_l, csg->shape.cylinder.h))
		return (free2(ray_pos_l, ray_dir_l), NULL);
	col = new_collision(obj, csg, ray, t_col[0]);
	col->norm = cy_get_norm(col, (t_vector*[2]){ray_pos_l, ray_dir_l}, theta, theta, t_col[1]);
	return (free2(ray_pos_l, ray_dir_l), col);
}


// OBSOLETE
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	(void)col;
}
