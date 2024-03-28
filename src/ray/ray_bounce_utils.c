#include "../../includes/miniRt.h"

t_rgb	color_combination(t_rgb *rgb, t_rgb *color_reflechie, t_rgb *color_refractee, float refract, float reflect)
{
	t_rgb	result;
	t_rgb	reflect_color;
	t_rgb	refract_color;

	reflect_color = vec_rgb(\
		color_reflechie->r * reflect, \
		color_reflechie->g * reflect, \
		color_reflechie->b * reflect);
	refract_color = vec_rgb(\
		color_refractee->r * refract, \
		color_refractee->g * refract, \
		color_refractee->b * refract);
	// if (reflect == 1)
	// {
	// 	result = vec_rgb(\
	// 	reflect_color.r + refract_color.r, \
	// 	reflect_color.g + refract_color.g, \
	// 	reflect_color.b + refract_color.b);
	// 	return (result);
	// }
	result = vec_rgb(\
		rgb->r + reflect_color.r + refract_color.r, \
		rgb->g + reflect_color.g + refract_color.g, \
		rgb->b + reflect_color.b + refract_color.b);
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

void	colorlocal(t_collision *collision, t_ray *ray)
{
	t_lcol	*light_col;
	t_rgb	rgb;

	(void)ray;
	light_col = query_visible_light(collision);
	if (!light_col)
		rgb = (t_rgb){0, 0, 0};
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

t_vector	*refract_calculation(t_vector *tmp, float indice_refract, \
	t_vector *ray)
{
	t_vector	*tmp2;
	t_vector	*refract;

	tmp2 = vec_mult(indice_refract, ray);
	refract = vec_add_inplace(tmp2, tmp);
	vec_normalize(refract);
	return (refract);
}
