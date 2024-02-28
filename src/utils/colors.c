/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:39:38 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 14:56:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "color_texture.h"

void	print_rgb(t_rgb *color)
{
	if (color)
		printf(" %3d r, %3d g, %3d b\n", color->r, color->g, color->b);
	else
		printf("NULL\n");
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
