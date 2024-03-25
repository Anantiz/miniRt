/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bounce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:26:07 by loris             #+#    #+#             */
/*   Updated: 2024/03/25 11:22:08 by aurban           ###   ########.fr       */
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

bool	ray_fract(t_vector *normal, t_vector *ray, float indice_refract, t_vector **refract)
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
	{
		*refract = NULL;
		printf("XXX\n");
		return (false); // reflection totale interne
	}
	cost = sqrt(1.0 - sin2t);
	t_vector	*tmp = vec_mult(indice_refract * cosi - cost, normal);
	*refract = vec_add_inplace(vec_mult(indice_refract, ray), tmp);
	our_free(tmp);
	return (true);
}

t_rgb	color_combination(t_rgb *rgb, t_rgb *colorReflechie, t_rgb *colorRefractee, float refract, float reflect)
{
	t_rgb	result;
	t_rgb	reflectColor;
	t_rgb	refractColor;

	(void)refract;
	reflectColor = vec_rgb(colorReflechie->r * reflect, colorReflechie->g * reflect, colorReflechie->b * reflect);
	refractColor = vec_rgb(colorRefractee->r * reflect, colorRefractee->g * reflect, colorRefractee->b * refract);
	result = vec_rgb(rgb->r + colorReflechie->r + colorRefractee->r, \
		rgb->g + colorReflechie->g + colorRefractee->g, \
		rgb->b + colorReflechie->b + colorRefractee->b);
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}

void	colorLocal(t_collision *collision, t_ray *ray)
{
	t_lcol	*light_col;
	t_rgb	rgb;

	light_col = query_visible_light(collision->csg, &collision->point, ray->dir);
	if (!light_col)
		rgb = vec_rgb(10,10,10);
	else
	{
		rgb = vec_rgb(\
			light_col->cos_angle * collision->csg->rgb.r, \
			light_col->cos_angle * collision->csg->rgb.g, \
			light_col->cos_angle * collision->csg->rgb.b);
	}
	collision->csg->rgb = rgb;
}

t_rgb	vec_rgb(int32_t x, int32_t y, int32_t z)
{
	t_rgb	rgb;

	rgb.r = x;
	rgb.g = y;
	rgb.b = z;
	return (rgb);
}

t_rgb	trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_collision	*col;
	t_ray		*ray_fraction;
	t_ray		*ray_flection;

	t_rgb		colorReflechie;
	t_rgb		colorRefractee;
	t_rgb		ret;

	ray_flection = our_malloc(sizeof(t_ray));
	ray_fraction = our_malloc(sizeof(t_ray));
	col = query_collision(scene, ray);
	if (depth == 0)
		return (vec_rgb(0, 0, 0));
	if (!col)
		return (vec_rgb(35, 35, 35));
	colorReflechie = vec_rgb(0, 0, 0);
	colorRefractee = vec_rgb(0, 0, 0);
	colorLocal(col, ray);
	if (col)
	{
		col->csg->reflect = 1;
		col->csg->refract = 1;
		if (col->csg->reflect > 0 && depth > 0)
		{
			ray_flection->pos = vec_copy(&col->point);
			ray_flection->dir = ray_flect(ray, col->norm);
			colorReflechie = trace_ray(ray_flection, scene, depth - 1);
		}
		if (col->csg->refract > 0 && depth > 0)
		{
			ray_fraction->pos = vec_copy(&col->point);
			if (ray_fract(col->norm, ray->dir, col->csg->refract, &ray_fraction->dir))
			{
				colorRefractee = trace_ray(ray_fraction, scene, depth - 1);
			}
		}
	}
	ret = color_combination(&col->csg->rgb, &colorReflechie, &colorRefractee, col->csg->reflect, col->csg->refract);
	return (ret);
}

