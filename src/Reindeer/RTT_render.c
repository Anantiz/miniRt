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

		printf("Camera:\n");
		printf("\tPos:        ");
		print_vector(glob->camera->pos);
		printf("\tDir:        ");
		print_vector(glob->camera->dir);
		printf("\tRight_normal: ");
		print_vector(glob->camera->right);
		printf("\tUp_normal:    ");
		print_vector(glob->camera->up);
		printf("\n");
	}
}

void	rtt_render_pixel(t_rgb *rgb, t_glob *glob, int x, int y)
{
	mlx_put_pixel(glob->img, x, y, vector_to_color(1, rgb));
}
