#include "miniRt.h"

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	ray_tracing(glob);
	sleep(5);
	// Do the rendering here
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
void	rtt_render_pixel(t_glob *glob, t_collision *collision, float u, float v)
{
	if (!collision || u >= WIN_SIZE_X || v >= WIN_SIZE_Y || u < 0 || v < 0)
		return ;
	// printf("Collision at %f, %f\n", u, v);
	mlx_put_pixel(glob->img, (int)u, (int)v, get_collision_color(collision));
}