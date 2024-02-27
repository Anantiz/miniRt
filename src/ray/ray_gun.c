#include "../../includes/miniRt.h"

FILE *debug_log_f;
void	normalize_coordinates(float *u, float *v, int x, int y)
{
	*u = (2 * ((x + 0.5) / WIN_SIZE_X) - 1);
	*v = (1 - 2 * ((y + 0.5) / WIN_SIZE_Y));
}

t_ray	*new_ray(t_camera *camera, int x, int y)
{
	t_ray		*ray;
	t_screen	*screen;
	float		u, v;

	normalize_coordinates(&u, &v, x, y);
	screen = field_of_view(camera->fov, (float)WIN_SIZE_X / (float)WIN_SIZE_Y);
	ray = our_malloc(sizeof(t_ray));
	ray->origin = new_vector(camera->pos->x, camera->pos->y, camera->pos->z);
	ray->direction = ray_dir(camera, screen, u, v);
	our_free(screen);
	fprintf(debug_log_f, "\tDir: %f, %f, %f\n", ray->direction->x, ray->direction->y, ray->direction->z);
	return (ray);
}

t_screen	*field_of_view(float fov, float aspect_ratio)
{
	t_screen	*screen;
	float		fov_radian;

	fov_radian = fov * (M_PI / 180);

	fprintf(debug_log_f, "\taspect_ratio: %f\n", aspect_ratio);
	screen = our_malloc(sizeof(t_screen));
	screen->width_factor = aspect_ratio * tanf(fov_radian / 2);
	screen->height_factor = tanf(fov_radian / 2);
	fprintf(debug_log_f, "\twidth height: %f, %f\n", screen->width_factor, screen->height_factor);
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
	debug_log_f = fopen("rendering.log", "w");
	while (x < WIN_SIZE_X)
	{
		y = 0;
		while (y < WIN_SIZE_Y)
		{
			// fprintf(debug_log_f, "Ray at %d, %d\n", x, y);
			ray = new_ray(glob->camera, x, y);
			collision = scene_collision_query(glob->scene, ray);
			if (collision)
			{
				// Bounce
				// Then get color at the end
			}

			rtt_render_pixel(glob, collision, x, y);
			our_free(ray->origin);
			our_free(ray->direction);
			our_free(ray);
			// fprintf(debug_log_f, "\n");
			y++;
		}
		x++;
	}
	fclose(debug_log_f);
	printf("Rendering done\n");
}
