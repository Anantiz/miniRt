#include "miniRt.h"

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

uint32_t	rgb_to_uint(t_rgb *rgb)
{
	uint32_t	color;

	color = rgb->g;
	color = (color << 8) + rgb->g;
	color = (color << 8) + rgb->b;
	color = (color << 8) + 0xFF; // Alpha
	return (color);
}

void	rtt_render_pixel(t_glob *glob, t_collision *collision, int x, int y)
{
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
		mlx_put_pixel(glob->img, x, y, 0x888888FF);
	else
	{
		mlx_put_pixel(glob->img, x, y, rgb_to_uint(&collision->obj->l->rgb));
		fprintf(debug_log_f, "\t~Collision\n");
	}
}
