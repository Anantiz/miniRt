#include "../../includes/miniRt.h"

#define DEL_LEN 9

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;
	char	del[DEL_LEN];
	int		i;

	glob = (t_glob *)glob_;
	i = 0;
	while (i < DEL_LEN)
		del[i++] = '\b';
	if (glob->update)
	{
		ft_printf("\033[94mRendering new frame: \033[0m");
		if (glob->tick == 0)
			ft_printf("\n");
		if (glob->tick != 0)
			ft_printf("\033[31m(wait)...\033[0m");
		ray_tracing(glob);
		if (glob->tick != 0)
			write(1, del, DEL_LEN);
		ft_printf("\033[32mRendering done\033[0m\n");
		glob->update = false; // Done rendering
		glob->tick++;
	}
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

