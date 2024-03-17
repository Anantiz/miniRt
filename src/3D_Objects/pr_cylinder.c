/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:57 by aurban            #+#    #+#             */
/*   Updated: 2024/03/17 16:51:34 by aurban           ###   ########.fr       */
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

//OK!
t_vector	*vec_matrix_rotate(t_vector *v, float theta[3])
{
	float cos_x = cosf(theta[0]);
	float sin_x = sinf(theta[0]);
	float cos_y = cosf(theta[1]);
	float sin_y = sinf(theta[1]);
	float cos_z = cosf(theta[2]);
	float sin_z = sinf(theta[2]);

	// Perform X-axis rotation
	float new_y = v->y * cos_x - v->z * sin_x;
	float new_z = v->y * sin_x + v->z * cos_x;
	// Perform Y-axis rotation
	float new_x = v->x * cos_y + new_z * sin_y;
	new_z = -v->x * sin_y + new_z * cos_y;
	// Perform Z-axis rotation
	float rotated_x = new_x * cos_z - new_y * sin_z;
	float rotated_y = new_x * sin_z + new_y * cos_z;

	// Allocate memory for the rotated vector
	t_vector *ret = our_malloc(sizeof(t_vector));
	ret->x = rotated_x;
	ret->y = rotated_y;
	ret->z = new_z; // Z-axis rotation result
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
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
// Note the extra-ammount of variables, it's to make the code more readable
// I make it cleaner once it works

// General variables
	float			h;
	float			r;
	h = csg->l->shape.cylinder.height;
	r = csg->l->shape.cylinder.rad;
// Global coordinates
	t_vector		*cy_axis_g;
	t_vector		*cy_origin_g;
	cy_origin_g = vec_add(&obj->pos, &csg->l->pos);
	cy_axis_g = vec_add(&obj->dir, &csg->l->dir);
// Local coordinates
	/*
		The cylinder's origin will be the origin of the local coordinates

		We need to find the transformation matrix that will convert the given
		cylinder's axis to the z-axis, then apply it to the ray origin and direction
		Objective:
			From: cy_origin_g + cy_axis_g == Some_point
			To  : cy_origin_l + cy_axis_l == z_axis + {0,0,0} == {0,0,1}
	*/
	/* STEP-1: Find the conversion Matrix*/
	//OK!
	float		angles[3];
	angles[0] = atan2(cy_axis_g->y, cy_axis_g->z);
	angles[1] = atan2(cy_axis_g->x, cy_axis_g->z);
	angles[2] = atan2(cy_axis_g->x, cy_axis_g->y);
	t_vector	*ray_pos_l;
	t_vector	*ray_dir_l;
	t_vector	*tmp;
	tmp = vec_sub_inplace(vec_copy(ray->pos), cy_origin_g);
	ray_pos_l = vec_matrix_rotate(tmp, angles);
	our_free(tmp);
	ray_dir_l = vec_matrix_rotate(ray->dir, angles);
	vec_normalize(ray_dir_l);

	/* STEP-2: Solve the equation*/
	/*
		Infinite cylinder equation:
			x² + y² = r²
		Then just check if z is in the range [0, h]
	*/
	float			t_circle; // The collision point on the circle (entrance or exit)
	t_pair_float	t;
	float			a;
	float			b;
	float			c;

		// static int sample = 0;
		// sample++;
	/*Ray-Circle intersection:
		((ray_dir.x * t) - ray_pos)² + ((ray_dir.y * t) - ray_pos)² = r²
		We somehow are lacking the cap of the cylinder
	*/
	a = ray_dir_l->x * ray_dir_l->x + ray_dir_l->y * ray_dir_l->y;
	b = 2 * (ray_dir_l->x * ray_pos_l->x + ray_dir_l->y * ray_pos_l->y);
	c = ray_pos_l->x * ray_pos_l->x + ray_pos_l->y * ray_pos_l->y - r * r;
	quadratic_solver(a, b, c, &t);
	t_circle = smallest_pos(t.t1, t.t2);

	/*Ray-Cap intersection:
		We need to check if the ray hits the caps of the cylinder
		Check if you collide with the normal plane
		Then check the distance to the center of the circle is within the radius
	*/
	// Check the bottom cap
	float		t_cap;
	float		t_caps[2];
	float		t_caps_dist[2];

	t_caps[0] = plane_intersection(&(t_vector){0, 0, 0}, &(t_vector){0, 0, 1}, ray_pos_l, ray_dir_l);
	t_caps[1] = plane_intersection(&(t_vector){0, 0, h}, &(t_vector){0, 0, 1}, ray_pos_l, ray_dir_l);
	t_vector	*tmp_col_cap;

	// Get collision with caps
		tmp =  vec_mult(t_caps[0], ray_dir_l);
		tmp_col_cap = vec_add(ray_pos_l, tmp);
		t_caps_dist[0] = vec_dist(tmp_col_cap, &(t_vector){0, 0, 0});

		// if (sample % 10000 == 0){
		// 	printf("t_caps[0]:%f\tt_caps_dist[0]: %f",t_caps[0], t_caps_dist[0]);
		// 	print_vector(tmp_col_cap);
		// }
		if (t_caps_dist[0] > r)
			t_caps[0] = -1;
		our_free(tmp);
		our_free(tmp_col_cap);

		tmp =  vec_mult(t_caps[1], ray_dir_l);
		tmp_col_cap = vec_add(ray_pos_l, tmp);
		t_caps_dist[1] = vec_dist(tmp_col_cap, &(t_vector){0, 0, h});
		// if (sample % 10000 == 0){
		// 	printf("t_caps[1]:%f\tt_caps_dist[1]: %f",t_caps[1], t_caps_dist[1]);
		// 	print_vector(tmp_col_cap);
		// }
		if (t_caps_dist[1] > r)
			t_caps[1] = -1;
		our_free(tmp);
		our_free(tmp_col_cap);

	// Get the closest collision
	t_cap = smallest_pos(t_caps[0], t_caps[1]);
	// if (sample % 10000 == 0){
	// 	// printf("t_cap: %f\n", t_cap);
	// 	// printf("t_circle: %f\n\n", t_circle);
	// }
	if (t_cap < t_circle && t_cap > 0)
	{
		printf("\033[31mCAP\033[0m\n");
	}

	// Now take the closest collision point between the circle and the caps
	float		t_col; // The actual collision point
	t_col = smallest_pos(t_circle, t_cap);
	if (t_col < 0)
		return (free2(ray_pos_l, ray_dir_l), free2(cy_axis_g, cy_origin_g), NULL);

	vec_mult_inplace(t_col, ray_dir_l);
	if (vec_add_inplace(ray_pos_l, ray_dir_l)->z > h || ray_pos_l->z < 0)
		return (free2(ray_pos_l, ray_dir_l), free2(cy_axis_g, cy_origin_g), NULL);
	free4(ray_pos_l, ray_dir_l, cy_axis_g, cy_origin_g);
	return (new_collision(obj, csg, ray, t_col));
}

/*

*/
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*cy_data;
	t_vector	*tmp;

	(void)ray;
	/*
		To get the closest point on the axis, the idea is:
			Get a vector that is orthogonal to both the axis and the collision
			point, this vector will be the normal we want, make sure it's in the
			correct direction (point + normal = center_axis(at the same height))

		Since both the point and the axis are collinear, the cross product will
		give us a vector orthogonal to both, thus parallel to the cylinder's base
	*/
	cy_data = vec_add(&col->parent_obj->pos, &col->obj->l->pos);
	tmp = vec_sub(&col->point, cy_data);
	cy_data = vec_realloc(&cy_data, vec_add(&col->parent_obj->dir, &col->obj->l->dir));
	vec_normalize(cy_data);
	vec_normalize(tmp);
	// Maybe we should do smthing if it's on the side or the cap
	col->norm = vec_cross_product(tmp, cy_data);
	our_free(cy_data);
	vec_normalize(col->norm);
	// vec_negate(col->norm);
}

