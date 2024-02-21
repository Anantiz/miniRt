/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:01:39 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 18:48:34 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

int main(int argc, char **argv)
{
	t_scene	*scene;

	scene = scene_new();
	if (argc != 2)
	{
		printf("\033[32mUsage: ./miniRT <scene.rt>\033[0m\n");
		return (FAILURE);
	}
	if (parse_map(scene, argv[1]))
		return (FAILURE);
	return (0);
}
