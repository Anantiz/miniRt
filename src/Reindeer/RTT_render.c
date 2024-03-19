#include "../../includes/miniRt.h"

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	// ray_tracing(glob);
	// sleep(5);
	(void)glob;
}

long my_x = 0;
long my_y = 0;

void	rtt_render_pixel(t_glob *glob, t_collision *collision, int x, int y, t_ray *ray)
{
	t_lcol *light_col;

	(void)ray;
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
	{
		mlx_put_pixel(glob->img, x, y, BLACK);
		return ;
	}
	my_x = x;
	my_y = y;
	light_col = query_visible_light(collision);
	if (!light_col) // Means the point is in the shadow
	{
		// mlx_put_pixel(glob->img, x, y, vector_to_color(0.25, &collision->csg->rgb));
		mlx_put_pixel(glob->img, x, y, DARK_GREY);
		return ;
	}
	mlx_put_pixel(glob->img, x, y, vector_to_color(light_col->cos_angle, &collision->csg->rgb));
	del_light_col(light_col);
	del_collision(collision);
}

