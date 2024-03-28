/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:06:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/28 12:39:35 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

#define INTER_CAP_SIDE 1
#define INTER_CIRCLE_SIDE -1

t_csg	*pr_new_cone(t_vector coordinates[2], char **params)
{
	t_csg	*cn;

	cn = our_malloc(sizeof(t_csg));
	cn->type = LEAF;
	cn->l = our_malloc(sizeof(t_leaf));
	cn->l->type = CONE;
	cn->l->pos = coordinates[0];
	cn->l->dir = coordinates[1];
	if (!parse_double(params[0], &cn->l->shape.cone.r))
		return (NULL);
	cn->l->shape.cylinder.r /= 2;
	if (!parse_double(params[1], &cn->l->shape.cone.h))
		return (NULL);
	cn->l->shape.cone.r2 = pow(cn->l->shape.cone.r, 2);
	cn->l->shape.cone.h2 = pow(cn->l->shape.cone.h, 2);
	if (!parse_rgb(&cn->l->rgb, params[2]))
		return (NULL);
	cn->l->reflect = 1.5;
	cn->l->refract = 0;
	return (cn);
}

double	cone_equation(t_vector *ray_pos, t_vector *ray_dir, double r2, double h2)
{
	t_pair_double	t;
	double		a;
	double		b;
	double		c;

	a = ray_dir->x * ray_dir->x + ray_dir->y * ray_dir->y - ray_dir->z * ray_dir->z * (r2 / h2);
	b = 2 * (ray_dir->x * ray_pos->x + ray_dir->y * ray_pos->y - ray_dir->z * ray_pos->z *  (r2 / h2));
	c = ray_pos->x * ray_pos->x + ray_pos->y * ray_pos->y - ray_pos->z * ray_pos->z *  (r2 / h2);
	if (!quadratic_solver(a, b, c, &t))
		return (-INFINITY);
	return (smallest_pos(t.t1, t.t2));
}

/*
	Evolution of radius with height:
		r = r_max * (1 - (z / h))
*/
static bool	cone_get_t(double t_col[2], t_vector *ray_pos_l, t_vector *rdir_l, double h)
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

inline t_vector	cone_get_norm(t_collision *col, t_vector *ray_l[2], \
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

t_collision	*collider_cone(t_object *obj, t_leaf *csg, t_ray *ray)
{
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

	t_col[0] = cone_equation(&ray_pos_l, &ray_dir_l, \
		csg->shape.cone.r2, csg->shape.cone.h2);
	// t_col[1] = cy_cap_intersection(&ray_pos_l, &ray_dir_l, \
	// 	csg->shape.cylinder.r2, csg->shape.cylinder.h);
	t_col[1] = -INFINITY;

	if (!cone_get_t(t_col, &ray_pos_l, &ray_dir_l, csg->shape.cylinder.h))
		return (NULL);
	col = new_collision(obj, csg, ray, t_col[0]);
	col->norm = cone_get_norm(col, (t_vector*[2]){&ray_pos_l, &ray_dir_l}, theta, t_col[1]);
	return (col);
}

// OBSOLETE, but required because invoked by new_collision
void	collider_cone_norm(t_collision *col, t_ray *ray)
{
	(void)ray;
	(void)col;
}
