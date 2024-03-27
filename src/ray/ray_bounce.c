#include "../../includes/miniRt.h"

static inline void	del_ray(t_ray *ray)
{
	our_free(ray->dir);
	our_free(ray);
}

t_vector	*ray_flect(t_ray *ray, t_vector *normal)
{
	float		dot;
	t_vector	*new_ray;

	dot = vec_dot_product(ray->dir, normal);
	new_ray = vec_sub(ray->dir, vec_mult((2 * dot), normal));
	// vec_normalize(new_ray);
	return (new_ray);
}

bool	ray_fract(t_vector *normal, t_vector *ray, float indice_refract, t_vector **refract)
{
	float	cosi;
	float	sin2t;
	float	cost;

	vec_normalize(ray);
	vec_normalize(normal);
	cosi = -vec_dot_product(ray, normal);
	if (cosi < -1.0)
		cosi = -1.0;
	else if (cosi > 1.0)
		cosi = 1.0;
	sin2t = indice_refract * indice_refract * (1.0 - cosi * cosi);
	if (sin2t > 1.0)
	{
		*refract = NULL;
		return (false); // reflection totale interne
	}
	cost = sqrt(1.0 - sin2t);
	t_vector	*tmp = vec_mult(indice_refract * cosi - cost, normal);
	t_vector	*tmp2 = vec_mult(indice_refract, ray);
	*refract = vec_add_inplace(tmp2, tmp);
	vec_normalize(*refract);
	our_free(tmp);
	return (true);
}

t_rgb	color_combination(t_rgb *rgb, t_rgb *colorReflechie, t_rgb *colorRefractee, float refract, float reflect)
{
	t_rgb	result;
	t_rgb	reflectColor;
	t_rgb	refractColor;

	reflectColor = vec_rgb(\
		colorReflechie->r * reflect, \
		colorReflechie->g * reflect, \
		colorReflechie->b * reflect);

	refractColor = vec_rgb(\
		colorRefractee->r * refract, \
		colorRefractee->g * refract, \
		colorRefractee->b * refract);

	result = vec_rgb(\
		rgb->r + reflectColor.r + refractColor.r, \
		rgb->g + reflectColor.g + refractColor.g, \
		rgb->b + reflectColor.b + refractColor.b);

	// Cap the color to 255
	if (result.r > 255)
		result.r = 255;
	if (result.g > 255)
		result.g = 255;
	if (result.b > 255)
		result.b = 255;
	return (result);
}
t_rgb	rgb_mult(t_rgb *rgb, float mult)
{
	t_rgb	result;

	result.r = rgb->r * mult;
	result.g = rgb->g * mult;
	result.b = rgb->b * mult;
	return (result);
}

void	colorLocal(t_collision *collision, t_ray *ray)
{
	t_lcol	*light_col;
	t_rgb	rgb;

	(void)ray;
	light_col = query_visible_light(collision);
	if (!light_col)
	{
		rgb = (t_rgb){0,0,0};
	}
	else
	{
		rgb = rgb_mult(&collision->csg->rgb, light_col->cos_angle);
		del_light_col(light_col);
	}
	collision->rgb = rgb;
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

	if (depth == 0)
		return (vec_rgb(0, 0, 0));
	col = query_collision(scene, ray);
	if (!col)
		return (vec_rgb(35, 35, 35));
	ray_flection = our_malloc(sizeof(t_ray));
	ray_fraction = our_malloc(sizeof(t_ray));
	colorReflechie = vec_rgb(0, 0, 0);
	colorRefractee = vec_rgb(0, 0, 0);
	colorLocal(col, ray);

	col->csg->reflect = 1;
	col->csg->refract = 1.5;

	if (col->csg->reflect > 0 && depth > 0)
	{
		ray_flection->pos = vec_copy(&col->point);
		ray_flection->dir = ray_flect(ray, &col->norm);
		colorReflechie = trace_ray(ray_flection, scene, depth - 1);
	}

	if (col->csg->refract > 0 && depth > 0)
	{
		ray_fraction->pos = vec_copy(&col->point);
		if (ray_fract(&col->norm, ray->dir, col->csg->refract, &ray_fraction->dir))
		{
			colorRefractee = trace_ray(ray_fraction, scene, depth - 1);
		}
	}
	ret = color_combination(&col->rgb, &colorReflechie, &colorRefractee, col->csg->reflect, col->csg->refract);
	del_ray(ray_flection);
	del_ray(ray_fraction);
	del_collision(col);
	return (ret);
}

