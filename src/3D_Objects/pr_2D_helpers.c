/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_2D_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:33:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/13 11:52:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"



/*
t_pair_float --> float rx, float ry
ray 	--> Ray
sc		--> Shape center
sr		--> Shape radius (semi-axes)

Returns true if the ray intersects the ellipse
Returns false if the ray doesn't intersect the ellipse

Use (t_pair_float *sr)to store the two intersection points (memory reuse).

Standard process, Plug the ray equation into the ellipse equation
Then solve the quadratic equation
This is a 2D intersection, so we don't need to check the height

Height is checked in the cylinder intersection function.

Ellipse equation:
	(x - sc.x)^2 / sr.x^2 + (y - sc.y)^2 / sr.y^2 = 1
Ray equation pluged in:
	((rc.x + rd.x * t) - sc.x)^2 / sr.x^2 + ((rc.y + rd.y * t) - sc.y)^2 / sr.y^2 = 1

	Solve for t: (for all axis)
		c = rc - sc
		(c²/sr²)-1 + ((2*c*rd)/sr²)*t + (rd²/sr²)*t² = 0
		We have a quadratic equation:
			- a = (rd²/sr²)
			- b = (2*c*rd/sr²)
			- c = (c²/sr²)-1
		ATTENTION:
			Do this for x and y axis.
			(I just wrote it for a single axis for simplicity).

*/
bool	ellipse_intersection(t_pair_float *sr, t_vector *sc, t_ray *ray)
{
	float		a;
	float		b;
	float		c;
	float		sqrd;
	t_vector	*or; // Origin-Center whatever you wanna call it

	or = vec_sub(ray->pos, sc);
	sqrd = sr->t1 * sr->t1 + EPSILON;
	a = (ray->dir->x * ray->dir->x) / sqrd;
	b = (2 * (or->x * ray->dir->x)) / sqrd;
	c = (or->x * or->x) / sqrd;

	sqrd = sr->t2 * sr->t2 + EPSILON;
	a += (ray->dir->z * ray->dir->z) / sqrd;
	b += (2 * (or->z * ray->dir->z)) / sqrd;
	c += (or->z * or->z) / sqrd;

	our_free(or);
	return (quadratic_solver(a, b, c - 1, sr));
}

/*
	BULLSHIT:


Step 1: Create A circle

Step 2, ROTATE THE CIRCLE
	step 2.1: Measure the angle between the cylinder's axis and the y axis (our reference)
	step 2.2: Create the ellipse using this angle

Step 3: Check 2D collision with the ellipse
Step 4: Check if the collision is within the cylinder's height

t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray)
{
	t_pair_float	sr;// Stands for shape radius
	t_vector		*v;
	float			angle_x;
	float			angle_z;
	float			h;
	float			t;

	// Step 1 && 2
	v = vec_add(&csg->l->dir, &obj->dir); // V is the cylinder Axis
	vec_normalize(v);
	angle_x = vec2d_get_angle_rad(v, &(t_vector){1, 0, 0});
	angle_z = vec2d_get_angle_rad(v, &(t_vector){0, 0, 1});
	our_free(v);
	// DEBUG
	static int sample = 0;
	if (sample % 80000 == 0)
	{
		printf("angle_x: %f\tangle_z: %f\n", angle_x, angle_z);
		printf("\tBefore rotation\n");
		sr.t1 = csg->l->shape.cylinder.rad;
		sr.t2 = csg->l->shape.cylinder.rad;
		printf("\t\tsr.x: %f\n", sr.t1);
		printf("\t\tsr.y: %f\n", sr.t2);
	}
	rotate_circle(csg->l->shape.cylinder.rad, &sr, angle_x, angle_z);
	if (sample % 80000 == 0)
	{
		printf("\tAfter rotation\n");
		printf("\t\tsr.x: %f\n", sr.t1);
		printf("\t\tsr.y: %f\n", sr.t2);
		printf("\n");
	}
	sample++;

	// Step 3
	h = csg->l->shape.cylinder.height; // Shorter term for the height
	v = vec_add(&csg->l->pos, &obj->pos); // V is the cylinder center
	if (!ellipse_intersection(&sr, v, ray))
		return (our_free(v), NULL);
	// Step 4
	// Take the closest intersection (If the ray traverse the cylinder)
	if (sr.t1 < 0 || (sr.t2 > 0 && sr.t2 < sr.t1))
		t = sr.t2;
	else
		t = sr.t1;
	// Height check

	Find a way such that:
		it statys the height along the y axis
		it becomes the Diameter if alongx the x or z axis

	if (t < 0 || !(v->y + ray->pos->y + t * ray->dir->y <= h && v->y + ray->pos->y + t * ray->dir->y >= 0))
		return (our_free(v), NULL);
	return (our_free(v), new_collision(obj, csg, ray, t));
}
void	collider_cylinder_norm(t_collision *col, t_ray *ray)
{
	t_vector	*center_axis;

	(void)ray;
	center_axis = vec_add(&col->parent_obj->pos, &col->obj->l->pos);
	// As compared to a sphere, we have to ignore the height, because
	// Cylinder's normals are only defined by the circle's normals
	center_axis->y = col->point.y; // Kinda wrong if the cylinder don't point up
	col->norm = vec_sub(&col->point, center_axis);
	our_free(center_axis);
	vec_normalize(col->norm );
}

void	rotate_ellipse(float *rx, float *ry, float angle_x, float angle_z)
{
	float	tmp;

	tmp = *rx * cos(angle_x) - *ry * sin(angle_x);
	*ry = *rx * sin(angle_z) + *ry * cos(angle_z);
	*rx = tmp;
}

void	rotate_circle(float r, t_pair_float *sr, float angle_x, float angle_z)
{
	sr->t1 = r;
	sr->t2 = r;
	rotate_ellipse(&sr->t2, &sr->t1, angle_x, angle_z);
}

*/