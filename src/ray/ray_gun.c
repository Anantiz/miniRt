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
	return (ray_direction);
}

int	main()
{
	t_camera	*camera = new_camera(new_vector(0, 0, 0), new_vector(0, 0, 1), 90);
	t_ray	*ray = new_ray(camera, -1, 1);
	ft_fprintf(1, "x = %f\n", ray->direction->x);
	ft_fprintf(1, "y = %f\n", ray->direction->y);
	ft_fprintf(1, "z = %f\n", ray->direction->z);
}