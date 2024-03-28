#include "../../includes/miniRt.h"

t_vector	*ray_flect(t_ray *ray, t_vector *normal)
{
	float		dot;
	t_vector	*new_ray;
	t_vector	*tmp;

	dot = vec_dot_product(ray->dir, normal);
	tmp = vec_mult((2 * dot), normal);
	new_ray = vec_sub(ray->dir, tmp);
	// vec_normalize(new_ray);
	return (new_ray);
}

bool	ray_fract(t_collision *col, t_vector *ray, float indice_refract, t_ray *refract)
{
	float		cosi;
	float		sin2t;

	vec_normalize(ray);
	vec_normalize(&col->norm);
	cosi = -vec_dot_product(ray, &col->norm);
	if (cosi < -1.0)
		cosi = -1.0;
	else if (cosi > 1.0)
		cosi = 1.0;
	sin2t = indice_refract * indice_refract * (1.0 - cosi * cosi);
	if (sin2t > 1.0)
	{
		refract->dir = NULL;
		return (false); // reflection totale interne
	}
	refract->pos = vec_copy(&col->point);
	refract->dir = refract_calculation(vec_mult(indice_refract * cosi - sqrt(1.0 - sin2t), \
									&col->norm), indice_refract, ray);
	return (true);
}

bool	reflect_ray(int depth, t_ray *ray_flection, t_collision *col, t_ray *ray)
{
	if (depth > 0)
	{
		ray_flection->pos = vec_copy(&col->point);
		ray_flection->dir = ray_flect(ray, &col->norm);
		return (true);
	}
	return (false);
}

t_rgb	traceray_ret_condition(int	depth)
{
	if (depth == 0)
		return (vec_rgb(0, 0, 0));
	return (vec_rgb(35, 35, 35));
}

void	traceray_init(t_ray **ray_fraction, t_ray **ray_flection, t_rgb *colorReflect, t_rgb *colorRefract)
{
	*ray_flection = our_malloc(sizeof(t_ray));
	*ray_fraction = our_malloc(sizeof(t_ray));
	*colorReflect = vec_rgb(0, 0, 0);
	*colorRefract = vec_rgb(0, 0, 0);
}