#include "miniRt.h"

t_ray	*new_ray(t_camera *camera, float x, float y)
{
	t_ray		*ray;
	t_vector	*ray_dir;

	ray_dir = our_malloc(sizeof(t_vector));
	ray = our_malloc(sizeof(t_ray));
	ray->origin = new_vector(camera->pos->x, camera->pos->y, camera->pos->z);
}