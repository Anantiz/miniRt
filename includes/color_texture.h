/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:52 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 14:52:05 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_TEXTURE_H
# define COLOR_TEXTURE_H

# include <stdint.h>
# include "forward_declaration.h"

# define RED		0xFF000000
# define GREEN		0x00FF0000
# define BLUE		0x0000FF00
# define BLACK		0x000000FF
# define WHITE		0xFFFFFF00

# define ALPHA		0x000000FF

# define GREY		0x80808000
# define YELLOW		0xFFFF0000
# define CYAN		0x00FFFF00
# define MAGENTA	0xFF00FF00
# define PINK		0xFFC0CB00
# define ORANGE		0xFFA50000
# define PURPLE		0x80008000
# define BROWN		0xA52A2A00
# define LIME		0x00FF0000
# define OLIVE		0x80800000
# define TEAL		0x00808000
# define NAVY		0x00008000
# define MAROON		0x80000000
# define SILVER		0xC0C0C000
# define GOLD		0xFFD70000
# define BRONZE		0xCD7F32
# define COPPER		0xB8733300
# define PLATINUM	0xE5E4E200
# define TURQUOISE	0x40E0D000
# define EMERALD	0x50C87800
# define SAPPHIRE	0x08256700
# define RUBY		0xE0115F00
# define DIAMOND	0xB9F2FF00
# define AMETHYST	0x9966CC00
# define AQUAMARINE	0x7FFFD400
# define TOPAZ		0x19A97400
# define PERIDOT	0xE6E20000
# define GARNET		0x73363500
# define CITRINE	0xE4D00A00
# define JADE		0x00A86B00
# define ONYX		0x35383900
# define OPAL		0x9F9F9F00
# define PEARL		0xF0EAD600



typedef struct s_rgb
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
}t_rgb;

/*
	Transparency is between 0 and 1:
		0 being fully opaque and 1 being fully transparent
*/
typedef struct s_material_properties
{
	float	absorbtion_index;
	float	refraction_index;
	float	transparency;
}t_material_properties;
// Shorter alias
typedef t_material_properties t_mp;

/*
	To do, add Bump map texture
*/
typedef struct s_texture
{

}t_texture;

// Utils
uint32_t			rgb_to_uint(t_rgb *rgb);
void				print_rgb(t_rgb *color);

#endif