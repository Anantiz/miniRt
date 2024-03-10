/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_2D_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:33:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/10 19:39:57 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
	Update the semi-axes distance with respect to the given angle
	Null or None-init pointers forbidden
*/
void	rotate_ellipse(float *rx, float *ry, float angle)
{
	float	tmp;

	tmp = *rx;
	*rx = *rx * cosf(angle) - *ry * sinf(angle);
	*ry = tmp * sinf(angle) + *ry * cosf(angle);
}

/*
	Warper to initialize the ellipse semi-axes with the circle's radius
	Then call the rotate_ellipse function
	Null pointers forbidden

	Using a pair cuz the intersection function takes a pair as argument
	(to reduce the number of functions)
*/
void	rotate_circle(float r, t_pair_float *sr, float angle)
{
	sr->t1 = r;
	sr->t2 = r;
	rotate_ellipse(&sr->t2, &sr->t1, angle);
}

/*
	Cuz no more than 25 lines per function
	(stupid norm)
*/
static void ellipse_init_to_zero_cuz_norm(float *a, float *b, float *c_quadratic)
{
	*a = 0;
	*b = 0;
	*c_quadratic = 0;
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
	float		c_quadratic;
	float		sqrd;
	t_vector	*c;

	c = sub_vector(ray->pos, sc);
	ellipse_init_to_zero_cuz_norm(&a, &b, &c_quadratic);
	sqrd = sr->t1 * sr->t1;
	if (sqrd)
	{
		a += (ray->dir->x * ray->dir->x) / sqrd;
		b += (2 * (c->x * ray->dir->x)) / sqrd;
		c_quadratic += (c->x * c->x) / sqrd;
	}
	sqrd = sr->t2 * sr->t2;
	if (sqrd)
	{
		a += (ray->dir->y * ray->dir->y) / sqrd;
		b += (2 * (c->y * ray->dir->y)) / sqrd;
		c_quadratic += (c->y * c->y) / sqrd;
	}
	our_free(c);
	return (quadratic_solver(a, b, c_quadratic - 1, sr));
}
