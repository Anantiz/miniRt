/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:39:38 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 10:56:48 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "color_texture.h"
#include "miniRt.h"

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

	color = rgb->r;
	color = (color << 8) + rgb->g;
	color = (color << 8) + rgb->b;
	color = (color << 8) + 0xFF; // Alpha
	return (color);
}

uint32_t vector_to_color(t_vector *vec, float k)
{
	if (!vec)
		return (BLACK);
	uint8_t r = (uint8_t)(125.0f);
	uint8_t g = (uint8_t)(50.0f);
	uint8_t b = (uint8_t)(20.0f);
	uint8_t a = 255.0f * k;

	uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
	return color;
}