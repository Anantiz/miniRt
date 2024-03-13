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
	light_col = query_visible_light(collision->obj, &collision->point, ray->dir);
	if (!light_col) // Means the point is in the shadow
	{
		// We do this for now because we don't have ambient light
		mlx_put_pixel(glob->img, x, y, vector_to_color(0.25, &collision->obj->l->rgb));
		return ;
	}
	mlx_put_pixel(glob->img, x, y, vector_to_color(light_col->cos_angle, &collision->obj->l->rgb));
	del_light_col(light_col);
	del_collision(collision);
}

