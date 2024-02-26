#include "../../includes/miniRt.h"

FILE *asderlog;
void	normalize_coordinates(float *u, float *v, int x, int y)
{
	*u = (2 * ((x + 0.5) / WIN_SIZE_X) - 1);
	*v = (1 - 2 * ((y + 0.5) / WIN_SIZE_Y));
	fprintf(asderlog, "  UV: %f, %f\n", *u, *v);
}

t_ray	*new_ray(t_camera *camera, int x, int y)
{
	t_ray		*ray;
	t_screen	*screen;
	float		u, v;

	normalize_coordinates(&u, &v, x, y);
	screen = field_of_view(camera->fov, WIN_SIZE_X / WIN_SIZE_Y);
	ray = our_malloc(sizeof(t_ray));
	ray->origin = new_vector(camera->pos->x, camera->pos->y, camera->pos->z);
	ray->direction = ray_dir(camera, screen, u, v);
	our_free(screen);
	fprintf(asderlog, "  Direction: %f, %f, %f\n", ray->direction->x, ray->direction->y, ray->direction->z);
	return (ray);
}

t_screen	*field_of_view(float fov, float aspect_ratio)
{
	t_screen	*screen;

	screen = our_malloc(sizeof(t_screen));
	screen->width_factor = tanf(fov / 2);
	screen->height_factor = aspect_ratio * tan(fov / 2);
	fprintf(asderlog, "\twidth height: %f, %f\n", screen->width_factor, screen->height_factor);
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
	t_collision	*collision;;
	int			x;
	int			y;

	x = 0;
	asderlog = fopen("rendering.log", "w");
	while (x < WIN_SIZE_X)
	{
		y = 0;
		while (y < WIN_SIZE_Y)
		{
			ray = new_ray(glob->camera, x, y);
			// Write the ray to the log
			fprintf(asderlog, "Ray at %d, %d\n", x, y);
			fprintf(asderlog, "\tOrigin: %f, %f, %f\n", ray->origin->x, ray->origin->y, ray->origin->z);
			fprintf(asderlog, "\tDirection: %f, %f, %f\n", ray->direction->x, ray->direction->y, ray->direction->z);
			collision = scene_collision_query(glob->scene, ray);
			rtt_render_pixel(glob, collision, x, y);
			del_collision(collision);
			y++;
		}
		x++;
	}
	fclose(asderlog);
	printf("Rendering done\n");
}
