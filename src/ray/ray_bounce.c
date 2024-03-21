/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bounce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:26:07 by loris             #+#    #+#             */
/*   Updated: 2024/03/21 12:31:16 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRt.h"


t_vector	*ray_flect(t_ray *ray, t_vector *normal)
{
	float		dot;
	t_vector	*new_ray;

	dot = vec_dot_product(ray->dir, normal);
	new_ray = vec_sub(ray->dir, vec_mult((2 * dot), normal));
	return (new_ray);
}

bool	ray_fract(t_vector *normal, t_vector *ray, float indice_refract, t_vector *refract)
{
	float	cosi;
	float	sin2t;
	float	cost;

	vec_normalize(ray);
	vec_normalize(normal);
	cosi = vec_dot_product(ray, normal);
	if (cosi < -1.0)
		cosi = -1.0;
	else if (cosi > 1.0)
		cosi = 1.0;
	sin2t = indice_refract * indice_refract * (1.0 - cosi * cosi);
	if (sin2t > 1.0)
		return (false); // reflection toale interne
	cost = sqrt(1.0 - sin2t);
	refract = vec_add(vec_mult(indice_refract, ray), vec_mult(indice_refract * cosi - cost, normal));
	return (true);
}
t_rgb	*color_combination(t_rgb *rgb, t_rgb *colorReflechie, t_rgb *colorRefractee, float refract, float reflect)
{
	t_rgb	*result;
	t_rgb	*reflectColor;
	t_rgb	*refractColor;

	reflectColor = NULL;
	refractColor = NULL;
	result = NULL;
	reflectColor = vec_rgb(colorReflechie->r * reflect, colorReflechie->g * reflect, colorReflechie->b * reflect);
	refractColor = vec_rgb(colorRefractee->r * reflect, colorRefractee->g * reflect, colorRefractee->b * reflect);
	result = vec_rgb(rgb->r + colorReflechie->r + colorRefractee->r, rgb->g + colorReflechie->g + colorRefractee->g, rgb->b + colorReflechie->b + colorRefractee->b);

	return (result);
}

void	colorLocal(t_collision *collision, t_ray *ray)
{
	t_lcol	*light_col;
	t_rgb	*rgb;

	rgb = vec_rgb(collision->csg->rgb.r * 0.25, collision->csg->rgb.g * 0.25, collision->csg->rgb.b * 0.25);
	light_col = query_visible_light(collision->csg, &collision->point, ray->dir);
	if (!light_col)
		collision->csg->rgb = *rgb;
	collision->csg->rgb = *rgb;
}

t_rgb	*vec_rgb(float x, float y, float z)
{
	t_rgb	*vector;

	vector = our_malloc(sizeof(t_vector));
	vector->r = x;
	vector->g = y;
	vector->b = z;
	return (vector);
}

t_rgb	*trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_collision	*col;
	t_ray		*ray_fraction;
	t_ray		*ray_flection;
	t_rgb		*colorReflechie;
	t_rgb		*colorRefractee;
	t_rgb		*ret;

	ret = NULL;
	col = query_collision(scene, ray);

	if (depth == 0)
		return (vec_rgb(0, 0, 0));
	if (!col)
		return (vec_rgb(0, 0, 255));
	colorReflechie = vec_rgb(0, 0, 0);
	colorRefractee = vec_rgb(0, 0, 0);
	colorLocal(col, ray);
	if (col)
	{
		if (col->csg->reflect > 0)
		{
			ray_flection = NULL;
			ray_flection->pos = &col->point;
			ray_flection->dir = ray_flect(ray, col->norm);
			colorReflechie = trace_ray(ray_flection, scene, depth - 1);
		}
		if (col->csg->refract > 0)
		{
			ray_fraction = NULL;
			ray_fraction->pos = &col->point;
			if (ray_fract(col->norm, ray->dir, col->csg->refract, ray_fraction->dir))
			{
				ray_fraction->pos = &col->point;
				colorRefractee = trace_ray(ray_fraction, scene, depth - 1);
			}
		}
	}
	return (color_combination(&col->csg->rgb, colorReflechie, colorRefractee, col->csg->reflect, col->csg->refract));
}

