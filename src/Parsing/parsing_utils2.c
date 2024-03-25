/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 22:30:21 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:40:36 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

bool	parse_rgb(t_rgb *color, char *str_color)
{
	char	**rgb;

	rgb = ft_split(str_color, ',');
	if (ft_tablen(rgb) != 3)
		return ((void)printf("Invalid RGB, too many arguments: "\
		"%s\n", str_color), false);
	if (!parse_int(rgb[0], (int*)&color->r) || color->r < 0 || color->r > 255)
		return ((void)printf("Invalid RGB: %s\n", str_color), false);
	if (!parse_int(rgb[1], (int*)&color->g) || color->g < 0 || color->g > 255)
		return ((void)printf("Invalid RGB: %s\n", str_color), false);
	if (!parse_int(rgb[2], (int*)&color->b ) || color->b < 0 || color->b > 255)
		return ((void)printf("Invalid RGB: %s\n", str_color), false);
	free_double_char(rgb);
	return (true);
}

/*
	Note that we pase in reverse order, because for some reasons,
	The program computes the coordinates in reverse order, and
	I have no idea why
*/
bool	parse_position(t_vector *vector, char *str_pos)
{
	char	**xyz;

	xyz = ft_split(str_pos, ',');
	if (ft_tablen(xyz) != 3)
		return ((void)printf("Invalid position, too many arguments: "\
		"%s\n", str_pos), false);
	if (!parse_double(xyz[0], &vector->x))
		return ((void)printf("Invalid position: %s\n", str_pos), false);
	if (!parse_double(xyz[1], &vector->y))
		return ((void)printf("Invalid position: %s\n", str_pos), false);
	if (!parse_double(xyz[2], &vector->z))
		return ((void)printf("Invalid position: %s\n", str_pos), false);
	free_double_char(xyz);
	return (true);
}

/* Checks if the input is somewhat normalized */
bool	parse_orientation(t_vector *vector, char *dir_str)
{
	char	**xyz;

	xyz = ft_split(dir_str, ',');
	if (ft_tablen(xyz) != 3)
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[0], &vector->x))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[1], &vector->y))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[2], &vector->z))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	free_double_char(xyz);
	vec_normalize(vector);
	if (vector->x == 0 && vector->y == 0 && vector->z == 0)
	{
		parse_error_msg(ERROR_PARSE_ROT, "\n\tOrientation can't be 0,0,0, "\
		"that's the same as saying:\n\t\t-\"Bro look in the direction of nowhe"\
		"re\".\n\t Idiotic right ?\n");
		return (false);
	}
	return (true);
}

/* Checks if the input is somewhat normalized */
bool	parse_orientation_null_allowed(t_vector *vector, char *dir_str)
{
	char	**xyz;

	xyz = ft_split(dir_str, ',');
	if (ft_tablen(xyz) != 3)
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[0], &vector->x))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[1], &vector->y))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	if (!parse_double(xyz[2], &vector->z))
		return ((void)printf("Invalid orientation: %s\n", dir_str), false);
	free_double_char(xyz);
	vec_normalize(vector);
	return (true);
}
