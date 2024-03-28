#include "../../includes/miniRt.h"

static inline void	del_ray(t_ray *ray)
{
	our_free(ray->dir);
	our_free(ray);
}

t_rgb	trace_ray(t_ray *ray, t_scene *scene, int depth, t_rgb ret)
{
	t_collision	*col;
	t_ray		*ray_fraction;
	t_ray		*ray_flection;
	t_rgb		color_reflect;
	t_rgb		color_refract;

	col = query_collision(scene, ray);
	if (!depth || !col)
		return (traceray_ret_condition(depth));
	col->csg->reflect = 1;
	col->csg->refract = 0.2;
	traceray_init(&ray_fraction, &ray_flection, &color_reflect, &color_refract);
	colorlocal(col, ray);
	if (col->csg->reflect > 0 && reflect_ray(depth, ray_flection, col, ray))
		color_reflect = trace_ray(ray_flection, scene, depth - 1, (t_rgb) {0, 0, 0});
	if (col->csg->refract > 0 && depth > 0 && ray_fract(col, ray->dir, \
					col->csg->refract, ray_fraction))
		color_refract = trace_ray(ray_fraction, scene, depth - 1, (t_rgb) {0, 0, 0});
	ret = color_combination(&col->rgb, &color_reflect, &color_refract, \
					col->csg->reflect, col->csg->refract);
	del_ray(ray_flection);
	del_ray(ray_fraction);
	del_collision(col);
	return (ret);
}
