/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:01:39 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 11:24:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

#define SMALL_WIN_X	640
#define SMALL_WIN_Y	480

static void	init_global(t_glob *glob, t_scene *scene)
{
	glob->scene = scene;
	glob->win_size = (t_pair_size){SMALL_WIN_X, SMALL_WIN_Y};
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
	glob->camera = NULL;
}

int main(int argc, char **argv)
{
	t_glob	glob;
	t_scene	*scene;

	scene = scene_new();
	init_global(&glob, scene);
	if (argc != 2)
	{
		printf("\033[32mUsage: ./miniRT <scene.rt>\033[0m\n");
		return (FAILURE);
	}
	if (parse_map(scene, argv[1]))
		return (FAILURE);
	mlx_loop_hook(glob.mlx, rtt_render, &glob);
	mlx_loop(glob.mlx);
	mlx_terminate(glob.mlx);
	safe_as_fuck_malloc(0, NULL, SAFE_MALLOC_FREE_ALL);
	return (0);
}
