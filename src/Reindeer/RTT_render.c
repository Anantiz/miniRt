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

unsigned	get_collision_color(t_collision *collision)
{
	uint32_t	color;

	color = collision->obj->l->rgb.r;
	color = (color << 8) + collision->obj->l->rgb.g;
	color = (color << 8) + collision->obj->l->rgb.b;
	color = (color << 8) + 0xFF; // Alpha
	return (0);
}
void	rtt_render_pixel(t_glob *glob, t_collision *collision, int x, int y)
{
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
		mlx_put_pixel(glob->img, x, y, 0xAA00AAFF);
	else
	{
		mlx_put_pixel(glob->img, x, y, get_collision_color(collision));
		fprintf(debug_log_f, "   ~Collision\n");
	}
}