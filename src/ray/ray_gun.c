#include "../../includes/miniRt.h"

FILE *debug_log_f;
void	normalize_coordinates(float *u, float *v, int x, int y)
{
	static const float aspect_ratio_x = (float)WIN_SIZE_X / (float)WIN_SIZE_Y;
	static const float aspect_ratio_y = (float)WIN_SIZE_Y / (float)WIN_SIZE_X;

	float	tmp;
	float	angle;

	// For some reasons, the x-y plane is rotated 90 degrees arround z

	// Normalize the screen coordinates to camera coordinates -1 to 1
	*u = (2 * ((x + 0.5) / WIN_SIZE_X) - 1);
	*v = 1 - (2 * ((y + 0.5) / WIN_SIZE_Y));

	*v = -(*v);

	// Adjust the rotation of the camera
// 	tmp = *u;
// 	angle = M_PI / 2;
// 	*u = ((*u) * cos(angle) - (*v) * sin(angle)) * (aspect_ratio_y);
// 	*v = (tmp * sin(angle) + (*v) * cos(angle))  * (aspect_ratio_x);
}

t_ray	*new_ray(t_camera *camera, int x, int y)
{
	t_ray		*ray;
	t_screen	*screen;
	float		u, v;

	normalize_coordinates(&u, &v, x, y);
	screen = field_of_view(camera->fov);
	ray = our_malloc(sizeof(t_ray));
	ray->pos = new_vector(camera->pos->x, camera->pos->y, camera->pos->z);
	ray->dir = ray_dir(camera, screen, u, v);
	our_free(screen);
	// fprintf(debug_log_f, "\tDir: %f, %f, %f\n", ray->dir->x, ray->dir->y, ray->dir->z);
	return (ray);
}

t_screen	*field_of_view(float fov)
{
	static const float	aspect_ratio = (float)WIN_SIZE_X / (float)WIN_SIZE_Y;
	t_screen			*screen;
	float				fov_radian;

	fov_radian = fov * (M_PI / 180);
	screen = our_malloc(sizeof(t_screen));
	screen->width_factor = aspect_ratio * tanf(fov_radian / 2);
	screen->height_factor = tanf(fov_radian / 2);
	return (screen);
}

t_vector	*ray_dir(t_camera *camera, t_screen *screen, float u, float v)
{
	t_vector	*ray_direction;
	t_vector	*sum_vector;

	sum_vector = add_vector(mult_vector(screen->width_factor * u, camera->right), \
							mult_vector(screen->height_factor * v, camera->up));

	ray_direction = add_vector(camera->dir, sum_vector);
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
			collision = query_collision(glob->scene, ray);
			// if (collision)
			// {
			// 	// Bounce
			// 	// Then get color at the end
			// }

			rtt_render_pixel(glob, collision, x, y, ray);
			our_free(ray->pos);
			our_free(ray->dir);
			our_free(ray);
			// fprintf(debug_log_f, "\n");
			y++;
		}
		x++;
	}
	fclose(debug_log_f);
	printf("Rendering done\n");
}
