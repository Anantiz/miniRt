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

void	rtt_render_pixel(t_rgb *rgb, t_glob *glob, int x, int y)
{
	mlx_put_pixel(glob->img, x, y, vector_to_color(1, rgb));
}
