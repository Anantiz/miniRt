/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 13:09:00 by aurban           ###   ########.fr       */
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
	quadratic_solver(a, b, c, &t);
	return (smallest_pos(t.t1, t.t2));
}

double	cy_cap_intersection(t_vector *ray_pos, t_vector *ray_dir, double r, double h)
{
	t_vector	*cap_pos;
	t_vector	*ray_path;
	double		t1;
	double		t2;

	// Check height intersection
	t1 = (0 - ray_pos->z) / ray_dir->z;
	t2 = (h - ray_pos->z) / ray_dir->z;
	// Now check if the ray is inside the circle, else, it's not a collision
	cap_pos = vec_copy(ray_pos);
	ray_path = vec_mult(t1, ray_dir);
	cap_pos = vec_add_inplace(cap_pos, ray_path);
	if (cap_pos->x * cap_pos->x + cap_pos->y * cap_pos->y > r * r)
		t1 = -1;
	our_free(cap_pos);
	our_free(ray_path);
	cap_pos = vec_copy(ray_pos);
	ray_path = vec_mult(t2, ray_dir);
	cap_pos = vec_add_inplace(cap_pos, ray_path);
	if (cap_pos->x * cap_pos->x + cap_pos->y * cap_pos->y > r * r)
		t2 = -1;
	our_free(cap_pos);
	our_free(ray_path);
	return (smallest_pos(t1, t2));
}

void	cy_get_theta(double theta[3], t_vector *cy_axis_a, t_vector *cy_axis_b)
{
	theta[0] = atan2(cy_axis_a->y + cy_axis_b->y, cy_axis_a->z + cy_axis_b->z);
	theta[1] = atan2(cy_axis_a->x + cy_axis_b->x, cy_axis_a->z + cy_axis_b->z);
	theta[2] = 0;//atan2(cy_axis_a->x + cy_axis_b->x, cy_axis_a->y + cy_axis_b->y);
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

	sample++;
	//Part 1: Convert to local coordinates
	pos = vec_add(&obj->pos, &csg->pos);
	cy_get_theta(theta, &obj->dir, &csg->dir);

	rdir_l = vec_matrix_rotate(ray->dir, theta);
	// static int sampler = 0;
	if (print_allow)
	{
		tmp = vec_matrix_rotate(&obj->dir, theta);
		printf("\tTheta: %fx, %fy, %fz\n", theta[0], theta[1], theta[2]);
		printf("\tBefore: ");
		print_vector(&obj->dir);
		printf("\tAfter: ");
		print_vector(tmp);
		our_free(tmp);
		printf("\n");
	}

	tmp = vec_sub_inplace(vec_copy(ray->pos), pos);
	pos = vec_realloc(&pos, vec_matrix_rotate(tmp, theta));

	t_col[0] = -1; //Debug, to isolate the cap
	t_col[1] = -1; //Debug, to isolate the cap
	// Part 2: Get the collision
	t_col[0] = cy_circle_intersection(pos, rdir_l, \
		csg->shape.cylinder.rad);
	// t_col[1] = cy_cap_intersection(pos, rdir_l, \
	// 	csg->shape.cylinder.rad, csg->shape.cylinder.height);

	// Part 3: Get the closest collision
	// double t = smallest_pos(t_col[0], t_col[1]);
	double t = -69;
	if (t_col[0] > 0 || t_col[1] > 0)
	{
		if (t_col[0] < 0)
			t = t_col[1];
		else if (t_col[1] < 0)
			t = t_col[0];
		else
		{
			t = fmin(t_col[0], t_col[1]);
			// mlx_put_pixel(fetch_glob(NULL)->img, my_x, my_y, 0x0000FFFF);
		}
		if (print_allow)
		{
			printf("\tCOL\n");
			printf("\tt_col[0]: %f\n", t_col[0]);
			printf("\tt_col[1]: %f\n", t_col[1]);
			printf("\tt: %f\n", t);
		}
		vec_mult_inplace(t, rdir_l);
		if (vec_add_inplace(pos, rdir_l)->z > csg->shape.cylinder.height + EPSILON || pos->z < -EPSILON)
		{
			if (print_allow)
				printf("\tOut of bounds, z=%f\n\n", pos->z);
			return (free3(pos, rdir_l, tmp), NULL);
		}
	}
	else
	{
		if (print_allow)
		{
			printf("\tNO COL\n");
			printf("\tt_col[0]: %f\n", t_col[0]);
			printf("\tt_col[1]: %f\n", t_col[1]);
			printf("\tt: %f\n\n", t);
		}
		return (free3(pos, rdir_l, tmp), NULL);
	}
	printf("\n");
	return (free3(pos, rdir_l, tmp), new_collision(obj, csg, ray, t));
}

// static void	cy_check_cap(double a, double b)
// {
// 	if (b < 0)
// 		return ;
// 	if (a < 0 && b > 0)
// 		collider_cylinder_norm(NULL, NULL);
// 	else if (b < a)
// 		collider_cylinder_norm(NULL, NULL);
// }


/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	static bool	cap = false;
	t_vector	*norm;

	(void)ray;
	if (!col)
	{
		cap = true;
		return ;
	}
	// The norm of the cap plane is the same as the cylinder
	norm = vec_add(&col->obj->dir, &col->csg->dir);
	if (!cap) // But if we not on the cap it's the circle norm that we want
	{
		// The norm becomes the normal of the axis, but towards the collision point
	}
	else
		cap = false; // Reset the cap flag
	col->norm = norm;
}

