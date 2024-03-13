/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_2D_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:33:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/13 16:54:22 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
	Rotate a 2D ellipse, arround a specific Vector, `angle` is in radians
	and represents the angles between the initial ellipse orientation and it's
	final orientation
*/
void	rotate_ellipse(float *rx, float *ry, float angle_x, float angle_z)
{
	*rx = *rx * sin(angle_x);
	*ry = *ry * cos(angle_z);
}

/*
	Warper to initialize the ellipse semi-axes with the circle's radius
	Then call the rotate_ellipse function
	Null pointers forbidden

	Using a pair cuz the intersection function takes a pair as argument
	(to reduce the number of functions)
*/
void	rotate_circle(float r, t_pair_float *sr, float angle_x, float angle_z)
{
	sr->t1 = r;
	sr->t2 = r;
	rotate_ellipse(&sr->t1, &sr->t2, angle_x, angle_z);
}

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

	sqrd = sr->t1 * sr->t2 + EPSILON;
	a += (ray->dir->y * ray->dir->y) / sqrd;
	b += (2 * (or->y * ray->dir->y)) / sqrd;
	c += (or->y * or->y) / sqrd;
	// static int sample = 0;
	// if (++sample % 20000 == 0)
	// 	printf("Ellipse Y a=%f b=%f c=%f\n", (ray->dir->y * ray->dir->y) / sqrd,  (2 * (or->y * ray->dir->y)) / sqrd, (or->y * or->y) / sqrd);

	sqrd = sr->t2 * sr->t2 + EPSILON;
	a += (ray->dir->z * ray->dir->z) / sqrd;
	b += (2 * (or->z * ray->dir->z)) / sqrd;
	c += (or->z * or->z) / sqrd;

	our_free(or);
	return (quadratic_solver(a, b, c - 1, sr));
}
