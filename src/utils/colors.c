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

	color = (uint8_t)rgb->r;
	color = (color << 8) + (uint8_t)rgb->g;
	color = (color << 8) + (uint8_t)rgb->b;
	color = (color << 8) + (uint8_t)0xFF; // Alpha
	return (color);
}

uint32_t vector_to_color(float k, t_rgb *color)
{
	if (k < 0.0f)
		k = -k;
	// k = 1.5f; // Increase the brightness, for debug purposes
	k += 0.1f;
	k += k/2.0f;
	if (k > 1.0f)
		k = 1.0f;
	uint8_t r = (uint8_t)(color->r * k);
	uint8_t g = (uint8_t)(color->g * k);
	uint8_t b = (uint8_t)(color->b * k);
	// uint8_t a = 255.0f * k;
	uint8_t a = 255;

	uint32_t color_ = (r << 24) | (g << 16) | (b << 8) | a;
	return color_;
}
