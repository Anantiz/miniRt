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
		mlx_put_pixel(glob->img, x, y, BLACK);
	else
	{
		t_lcol *light_col;
		light_col = query_visible_light(collision->obj, &collision->point, ray->direction);
		vector_normalizer(&(collision->point));
		float angle;
		if (light_col)
			angle =  light_col->theta;
		else
			angle = 0;
		mlx_put_pixel(glob->img, x, y, vector_to_color(angle, &collision->obj->l->rgb));
	}
}

