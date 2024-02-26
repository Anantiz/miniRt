#include "../../includes/miniRt.h"

t_ray	*new_ray(t_camera *camera, float u, float v)
{
	t_ray		*ray;
	t_screen	*screen;

	screen = field_of_view(camera->fov, 1920 / 1080);
	ray = our_malloc(sizeof(t_ray));
	ray->origin = new_vector(camera->pos->x, camera->pos->y, camera->pos->z);
	ray->direction = ray_dir(camera, screen, u, v);
	return (ray);
}

t_screen	*field_of_view(float fov, float aspect_ratio)
{
	t_screen	*screen;

	screen = our_malloc(sizeof(t_screen));
	screen->width_factor = tan(fov / 2);
	screen->height_factor = aspect_ratio * tan(fov / 2);
	return (screen);
}

t_vector	*ray_dir(t_camera *camera, t_screen *screen, float u, float v)
{
	t_vector	*ray_direction;
	t_vector	*sum_vector;

	sum_vector = add_vector(mult_vector(screen->width_factor * u, camera->right), \
							mult_vector(screen->height_factor * v, camera->up));
	ray_direction = add_vector(camera->direction, sum_vector);
	our_free(sum_vector);
	vector_normalizer(ray_direction);
	return (ray_direction);
}

void	ray_tracing(t_glob *glob)
{
	t_ray		*ray;
	t_collision	*collision;
	float		pas;
	float		u;
	
	float		v;

	u = -1;
	v = -1 * (1080 / 1920);
	pas = 2.0 / 1920;
	while (u <= 1)
	{
		while (v <= 1080 / 1920)
		{
			ray = new_ray(glob->camera, u, v);
			collision = scene_collision_query(glob->scene,ray);
			rtt_render_pixel(glob, collision, u, v);
			v += pas;
		}
		u += pas;
	}
}
