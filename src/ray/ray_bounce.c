/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bounce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:26:07 by loris             #+#    #+#             */
/*   Updated: 2024/03/18 15:58:24 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRt.h"


t_vector	*ray_flect(t_ray *ray, t_vector *normal)
{
	float	dot;
	t_ray	*new_ray;

	dot = vec_dot_product(ray, normal);
	new_ray = vec_sub(ray, vec_mult((2 * dot), normal));
	return (new_ray);
}

bool	ray_fract(t_vector *normal, t_vector *ray, float indice_refract, t_vector *refract)
{
	float	cosi;
	float	sin2t;
	float	cost;

	vec_normalize(ray);
	vec_normalize(normal);
	cosi = produit_scalaire(ray, normal);
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
t_rgb	color_combination()
{

}

void	colorLocal(t_collision *collision, t_ray *ray)
{
	t_lcol	*light_col;

	light_col = query_visible_light(collision->obj, &collision->point, ray->dir);
	if (!light_col)
	{
		collision->obj->l->rgb.r = collision->obj->l->rgb.r * 0.25;
		collision->obj->l->rgb.g = collision->obj->l->rgb.g * 0.25;
		collision->obj->l->rgb.b = collision->obj->l->rgb.b * 0.25;
	}
	collision->obj->l->rgb.r = collision->obj->l->rgb.r * light_col->cos_angle;
	collision->obj->l->rgb.g = collision->obj->l->rgb.g * light_col->cos_angle;
	collision->obj->l->rgb.b = collision->obj->l->rgb.b * light_col->cos_angle;
}

t_rgb	*trace_ray(t_ray *ray, t_scene *scene, int depth)
{
	t_collision	*col;
	t_ray		*ray_fraction;
	t_ray		*ray_flection;
	t_rgb		*colorReflechie;
	t_rgb		*colorRefractee;

	col = query_collision(scene, ray);

	if (depth == 0)
		return (vec_new(0, 0, 0));
	if (!col)
		return (vec_new(255, 0, 0));
	colorReflechie = vec_new(0, 0, 0);
	colorRefractee = vec_new(0, 0, 0);
	colorLocal(col, ray);
	if (col)
	{
		if (col->csg->reflect > 0)
		{
			ray_flection->pos = &col->point;
			ray_flection->dir = ray_flect(ray, col->norm);
			colorReflechie = trace_ray(ray_flection, scene, depth - 1);
		}
		if (col->obj->l->refract > 0)
		{
			ray_fraction->pos = &col->point;
			if (ray_fract(col->norm, ray, col->obj->l->refract, ray_fraction->dir));
			{
				ray_fraction->pos = &col->point;
				colorRefractee = trace_ray(ray_fraction, scene, depth - 1);
			}
		}
	}
	return (color_combination(col->csg->rgb, colorReflechie, colorRefractee))
}

