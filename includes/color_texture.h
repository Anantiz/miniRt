/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:06:52 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 10:41:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_TEXTURE_H
# define COLOR_TEXTURE_H

# include <stdint.h>
# include "forward_declaration.h"

# define RED		0xFF0000FF
# define GREEN		0x00FF00FF
# define BLUE		0x0000FFFF
# define BLACK		0x000000FF
# define WHITE		0xFFFFFFFF

# define ALPHA		0x000000FF

# define GREY		0x808080FF
# define YELLOW		0xFFFF00FF
# define CYAN		0x00FFFFFF
# define MAGENTA	0xFF00FFFF
# define PINK		0xFFC0CBFF
# define ORANGE		0xFFA500FF
# define PURPLE		0x800080FF
# define BROWN		0xA52A2AFF
# define LIME		0x00FF00FF
# define OLIVE		0x808000FF
# define TEAL		0x008080FF
# define NAVY		0x000080FF
# define MAROON		0x800000FF
# define SILVER		0xC0C0C0FF
# define GOLD		0xFFD700FF
# define BRONZE		0xCD7F32FF
# define COPPER		0xB87333FF
# define PLATINUM	0xE5E4E2FF
# define TURQUOISE	0x40E0D0FF
# define EMERALD	0x50C878FF
# define SAPPHIRE	0x082567FF
# define RUBY		0xE0115FFF
# define DIAMOND	0xB9F2FFFF
# define AMETHYST	0x9966CCFF
# define AQUAMARINE	0x7FFFD4FF
# define TOPAZ		0x19A974FF
# define PERIDOT	0xE6E200FF
# define GARNET		0x733635FF
# define CITRINE	0xE4D00AFF
# define JADE		0x00A86BFF
# define ONYX		0x353839FF
# define OPAL		0x9F9F9FFF
# define PEARL		0xF0EAD6FF



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
uint32_t 			vector_to_color(t_vector *vec, float k);

#endif