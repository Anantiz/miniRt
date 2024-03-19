/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/03/19 12:41:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	parse_error_msg(int error, char *custom_str)
{
	char	*str;

	if (error == ERROR_PARSE_RGB)
		str = ft_strdup("Invalid color format");
	else if (error == ERROR_PARSE_POS)
		str = ft_strdup("Invalid position format");
	else if (error == ERROR_PARSE_ROT)
		str = ft_strdup("Invalid orientation format");
	else if (error == ERROR_PARSE_WRONG_COUNT)
		str = ft_strdup("Wrong parameters count");
	else if (error == ERROR_DUPLICATE_AMBIANT)
		str = ft_strdup("Ambiant light already set");
	else if (error == ERROR_DUPLICATE_CAM)
		str = ft_strdup("Camera already set");
	else if (error == ERROR_PARSE_FOV)
		str = ft_strdup("Invalid FOV format");
	else if (error == ERROR_PARSE_LINTESITY)
		str = ft_strdup("Invalid light intensity format");
	else if (error == ERROR_PARSE_INT)
		error_exit("Invalid integer format");
	else if (error == ERROR_PARSE_FLOAT)
		str = ft_strdup("Invalid double format");
	if (custom_str)
	{
		str = ft_strjoin(str, " : ");
		str = ft_strjoin(str, custom_str);
	}
	error_exit(str);
}

void	parse_rgb(t_rgb *color, char *str_color)
{
	char	**rgb;

	rgb = ft_split(str_color, ',');
	if (ft_tablen(rgb) != 3)
		error_exit("Wrong parameters count : color");
	color->r = parse_int(rgb[0]);
	if (color->r < 0 || color->r > 255)
		parse_error_msg(ERROR_PARSE_RGB, NULL);
	color->g = parse_int(rgb[1]);
	if (color->g < 0 || color->g > 255)
		parse_error_msg(ERROR_PARSE_RGB, NULL);
	color->b = parse_int(rgb[2]);
	if (color->b < 0 || color->b > 255)
		parse_error_msg(ERROR_PARSE_RGB, NULL);
	free_double_char(rgb);
}

/*
	Note that we pase in reverse order, because for some reasons,
	The program computes the coordinates in reverse order, and
	I have no idea why
*/
void	parse_position(t_vector *vector, char *str_pos)
{
	char	**xyz;

	xyz = ft_split(str_pos, ',');
	if (ft_tablen(xyz) != 3)
		error_exit(ft_strjoin("Wrong parameters count : position, "\
		"str_pos: ", str_pos));
	vector->x = parse_double(xyz[0]);
	vector->y = parse_double(xyz[1]);
	vector->z = parse_double(xyz[2]);
	free_double_char(xyz);
}

/* Checks if the input is somewhat normalized */
void	parse_orientation(t_vector *vector, char *dir_str)
{
	char	**xyz;

	xyz = ft_split(dir_str, ',');
	if (ft_tablen(xyz) != 3)
		error_exit("Wrong parameters count : orientation");
	vector->x = parse_double(xyz[0]);
	vector->y = parse_double(xyz[1]);
	vector->z = parse_double(xyz[2]);
	free_double_char(xyz);
	vec_normalize(vector);
	if (vector->x == 0 && vector->y == 0 && vector->z == 0)
		parse_error_msg(ERROR_PARSE_ROT, "\n\tOrientation can't be 0,0,0, "\
		"that's the same as saying:\n\t\t-\"Bro look in the direction of nowhe"\
		"re\".\n\t Idiotic right ?\n");
}

/* Checks if the input is somewhat normalized */
void	parse_orientation_private(t_vector *vector, char *dir_str)
{
	char	**xyz;

	xyz = ft_split(dir_str, ',');
	if (ft_tablen(xyz) != 3)
		error_exit("Wrong parameters count : orientation");
	vector->x = parse_double(xyz[0]);
	if (vector->x > 1 || vector->x < -1)
		parse_error_msg(ERROR_PARSE_ROT, NULL);
	vector->y = parse_double(xyz[1]);
	if (vector->y > 1 || vector->y < -1)
		parse_error_msg(ERROR_PARSE_ROT, NULL);
	vector->z = parse_double(xyz[2]);
	if (vector->z > 1 || vector->z < -1)
		parse_error_msg(ERROR_PARSE_ROT, NULL);
	free_double_char(xyz);
	vec_normalize(vector);
}

double	parse_double(char *str)
{
	if (!ft_is_float_format(str))
	{
		printf("Invalid double: %s\n", str);
		parse_error_msg(ERROR_PARSE_FLOAT, NULL);
	}
	return (ft_atoldb(str));
}
