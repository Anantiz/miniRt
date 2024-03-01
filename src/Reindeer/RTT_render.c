#include "../../includes/miniRt.h"

extern FILE *debug_log_f;

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	// ray_tracing(glob);
	// sleep(5);
	(void)glob;
}

void	rtt_render_pixel(t_glob *glob, t_collision *collision, int x, int y, t_ray *ray)
{
	(void)ray;
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
		mlx_put_pixel(glob->img, x, y, PINK);
	else
	{
		vector_normalizer(&(collision->point));
		mlx_put_pixel(glob->img, x, y, vector_to_color(collision->point));
		// fprintf(debug_log_f, "\t~Collision\n");
	}
}

// t_vector	*hit_point_to_color(t_collision *collision, t_ray *ray)
// {
// 	t_vector	*hitpoint;

// 	// hitpoint = mult_vector(collision->dist, ray->direction);
// 	// hitpoint = add_vector(ray->origin, hitpoint);
// 	hitpoint = collision->point;
// 	vector_normalizer(hitpoint);
// 	return (hitpoint);
// }