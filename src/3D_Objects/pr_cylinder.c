/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/18 11:53:43 by aurban           ###   ########.fr       */
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
t_csg	*pr_new_cylinder(char **params)
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
float	cy_circle_intersection(t_vector *ray_pos, t_vector *ray_dir, float r)
{
	t_pair_float	t;
	float			a;
	float			b;
	float			c;

	a = ray_dir->x * ray_dir->x + ray_dir->y * ray_dir->y;
	b = 2 * (ray_dir->x * ray_pos->x + ray_dir->y * ray_pos->y);
	c = ray_pos->x * ray_pos->x + ray_pos->y * ray_pos->y - r * r;
	quadratic_solver(a, b, c, &t);
	return (smallest_pos(t.t1, t.t2));
}

float	cy_cap_intersection(t_vector *ray_pos, t_vector *ray_dir, float r, float h)
{
	t_vector	*cap_pos;
	t_vector	*ray_path;
	float		t1;
	float		t2;

	// Check height intersection
	t1 = (0 - ray_pos->z) / ray_dir->z;
	t2 = (h - ray_pos->z) / ray_dir->z;
	// Now check if the ray is inside the circle, else, it's not a collision
	cap_pos = vec_copy(ray_pos);
	ray_path = vec_mult(t1, ray_dir);
	cap_pos = vec_add_inplace(cap_pos, ray_path);
	if (fabs(cap_pos->x) > r || fabs(cap_pos->y) > r)
		t1 = -1;
	our_free(cap_pos);
	our_free(ray_path);
	cap_pos = vec_copy(ray_pos);
	ray_path = vec_mult(t2, ray_dir);
	cap_pos = vec_add_inplace(cap_pos, ray_path);
	if (fabs(cap_pos->x) > r || fabs(cap_pos->y) > r)
		t2 = -1;
	our_free(cap_pos);
	our_free(ray_path);
	return (smallest_pos(t1, t2));
}

void	cy_get_theta(float theta[3], t_vector *cy_axis_a, t_vector *cy_axis_b)
{
	t_vector	*cy_axis_g;

	cy_axis_g = vec_add(cy_axis_a, cy_axis_b);
	theta[0] = atan2(cy_axis_g->y, cy_axis_g->z);
	theta[1] = atan2(cy_axis_g->x, cy_axis_g->z);
	theta[2] = atan2(cy_axis_g->x, cy_axis_g->y);
	our_free(cy_axis_g);
}

static void	cy_check_cap(float a, float b)
{
	if (b < 0)
		return ;
	if (a < 0 && b > 0)
		collider_cylinder_norm(NULL, NULL);
	else if (b < a)
		collider_cylinder_norm(NULL, NULL);
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
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_vector		*rdir_l;
	t_vector		*pos;
	t_vector		*tmp;
	float			theta[3];
	float			t_col[2];

	//Part 1: Convert to local coordinates
	pos = vec_add(&obj->pos, &csg->l->pos);
	cy_get_theta(theta, &obj->dir, &csg->l->dir);
	rdir_l = vec_matrix_rotate(ray->dir, theta);
	tmp = vec_sub_inplace(vec_copy(ray->pos), pos);
	pos = vec_realloc(&pos, vec_matrix_rotate(tmp, theta));

	//Part 2: Get the collision
	t_col[0] = cy_circle_intersection(pos, rdir_l, \
		csg->l->shape.cylinder.rad);
	t_col[1] = cy_cap_intersection(pos, rdir_l, \
		csg->l->shape.cylinder.rad, csg->l->shape.cylinder.height);

	// Part 3: Get the closest collision
	cy_check_cap(t_col[0], t_col[1]);
	t_col[0] = smallest_pos(t_col[0], t_col[1]);
	if (t_col[0] < 0)
		return (free3(pos, rdir_l, tmp), NULL);
	vec_mult_inplace(t_col[0], rdir_l);
	if (vec_add_inplace(pos, rdir_l)->z > csg->l->shape.cylinder.height || pos->z < 0)
		return (free3(pos, rdir_l, tmp), NULL);
	return (free3(pos, rdir_l, tmp), new_collision(obj, csg, ray, t_col[0]));
}

/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	static bool	cap = false;
	t_vector	*cy_data;
	t_vector	*tmp;


}

