#include "../../includes/miniRt.h"

void	normalize_coordinates(float *u, float *v, int x, int y)
{
	// Normalize the screen coordinates to camera coordinates -1 to 1
	*u = (2 * ((x + 0.5) / WIN_SIZE_X) - 1);
	*v = 1 - (2 * ((y + 0.5) / WIN_SIZE_Y));
	*v = -(*v);

//Rotate the camera if we ever need to
	// static const float aspect_ratio_x = (float)WIN_SIZE_X / (float)WIN_SIZE_Y;
	// static const float aspect_ratio_y = (float)WIN_SIZE_Y / (float)WIN_SIZE_X;
	// float	tmp;
	// float	angle;

	// Adjust the rotation of the camera
	// tmp = *u;
	// angle = M_PI / 2;
	// *u = ((*u) * cos(angle) - (*v) * sin(angle)) * (aspect_ratio_y);
	// *v = (tmp * sin(angle) + (*v) * cos(angle))  * (aspect_ratio_x);
}

t_ray	*new_ray(t_camera *camera, int x, int y)
{
	static t_screen	*screen;
	static bool		init = false;
	t_ray			*ray;
	float			u, v;

	if (!init)
	{
		screen = field_of_view(camera->fov);
		init = true;
	}
	normalize_coordinates(&u, &v, x, y);
	ray = our_malloc(sizeof(t_ray));
	ray->pos = camera->pos;
	ray->dir = ray_dir(camera, screen, u, v);
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
	t_vector	*fov_factor;

	// We want to have the ray go farther/closer depending on the fov
	fov_factor = vec_add(vec_mult(screen->width_factor * u, camera->right), \
							vec_mult(screen->height_factor * v, camera->up));

	ray_direction = vec_add(camera->dir, fov_factor);
	our_free(fov_factor);
	vec_normalize(ray_direction);
	return (ray_direction);
}

void	ray_tracing(t_glob *glob)
{
	t_ray		*ray;
	t_collision	*collision;;
	int			x;
	int			y;

	x = 0;
	while (x < WIN_SIZE_X)
	{
		y = 0;
		while (y < WIN_SIZE_Y)
		{
			ray = new_ray(glob->camera, x, y);
			collision = query_collision(glob->scene, ray);
			rtt_render_pixel(glob, collision, x, y, ray);
			our_free(ray->dir);
			our_free(ray);
			y++;
		}
		x++;
	}
	printf("Rendering done\n");
}
