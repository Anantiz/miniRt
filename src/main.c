/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:01:39 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 10:35:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

const char	*shape_names[] = {"Sphere", "Plane", "Cylinder", NULL, NULL, NULL, NULL, NULL};

static void	init_global(t_glob *glob)
{
	glob->win_size = (t_pair_size){WIN_SIZE_X, WIN_SIZE_Y};
	glob->mlx = mlx_init(glob->win_size.width, glob->win_size.height, \
	"RTT", false);
	if (!glob->mlx)
		error_exit("Failed to initialize MLX");
	glob->img = mlx_new_image(glob->mlx, glob->win_size.width , \
	glob->win_size.height);
	if (!glob->img)
	{
		mlx_terminate(glob->mlx);
		error_exit("Failed to initialize MLX image");
	}
	mlx_key_hook(glob->mlx, cptn_hook_key, glob);
}
void	my_test(t_glob *glob);

FILE *debug_log_f;

int main(int argc, char **argv)
{
	t_glob	glob;
	t_scene	*scene;

	if (argc != 2)
	{
		printf("\033[32mUsage: ./miniRT <scene.rt>\033[0m\n");
		return (FAILURE);
	}
	debug_log_f = fopen("rendering.log", "w");
	scene = scene_new();
	glob.scene = scene;
	glob.camera = NULL;
	if (parse_map(&glob, argv[1]))
		return (FAILURE);
	printf("\033[32mParsing done\033[0m\n");
	// my_test(&glob);
	init_global(&glob);
	ray_tracing(&glob);
	mlx_image_to_window(glob.mlx, glob.img, 0, 0);
	mlx_key_hook(glob.mlx, cptn_hook_key, &glob);
	mlx_loop(glob.mlx);
	mlx_terminate(glob.mlx);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
	gc_close_all();
	fclose(debug_log_f);
	return (0);
}
