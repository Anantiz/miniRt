/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 15:39:29 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	parse_error_msg(int error)
{
	if (error == ERROR_PARSE_RGB)
		error_exit("Invalid color format");
	if (error == ERROR_PARSE_POS)
		error_exit("Invalid position format");
	if (error == ERROR_PARSE_ROT)
		error_exit("Invalid rotation format");
	if (error == ERROR_PARSE_WRONG_COUNT)
		error_exit("Wrong parameters count");
	if (error == ERROR_DUPLICATE_AMBIANT)
		error_exit("Ambiant light already set");
	if (error == ERROR_DUPLICATE_CAM)
		error_exit("Camera already set");
	if (error == ERROR_PARSE_FOV)
		error_exit("Invalid FOV format");
	if (error == ERROR_PARSE_LINTESITY)
		error_exit("Invalid light intensity format");
	if (error == ERROR_PARSE_INT)
		error_exit("Invalid integer format");
	if (error == ERROR_PARSE_FLOAT)
		error_exit("Invalid float format");
}

void	parse_rgb(t_rgb *color, char *str_color)
{
	char	**rgb;

	rgb = ft_split(str_color, ',');
	if (ft_tablen(rgb) != 3)
		error_exit("Wrong parameters count : color");
	color->r = parse_int(rgb[0]);
	if (color->r < 0 || color->r > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	color->g = parse_int(rgb[1]);
	if (color->g < 0 || color->g > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	color->b = parse_int(rgb[2]);
	if (color->b < 0 || color->b > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	free_double_char(rgb);
}

void	parse_position(t_vector *vector, char *str_pos)
{
	char	**xyz;

	xyz = ft_split(str_pos, ',');
	if (ft_tablen(xyz) != 3)
		error_exit("Wrong parameters count : position");
	vector->x = parse_float(xyz[0]);
	vector->y = parse_float(xyz[1]);
	vector->z = parse_float(xyz[2]);
	free_double_char(xyz);
}

/* Checks if the input is somewhat normalized */
void	parse_orientation(t_vector *vector, char *str_rot)
{
	char	**xyz;

	xyz = ft_split(str_rot, ',');
	if (ft_tablen(xyz) != 3)
		error_exit("Wrong parameters count : orientation");
	vector->x = parse_float(xyz[0]);
	if (vector->x > 1 || vector->x < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	vector->y = parse_float(xyz[1]);
	if (vector->y > 1 || vector->y < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	vector->z = parse_float(xyz[2]);
	if (vector->z > 1 || vector->z < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	free_double_char(xyz);
	vector_normalizer(vector);
	if (vector->x == 0 && vector->y == 0 && vector->z == 0)
		error_exit("Invalid orientation, must be non null");
}

float	parse_float(char *str)
{
	if (!ft_is_float_format(str))
		parse_error_msg(ERROR_PARSE_FLOAT);
	return (ft_atoldb(str));
}
