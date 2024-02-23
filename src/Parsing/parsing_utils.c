/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/02/23 14:27:42 by aurban           ###   ########.fr       */
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
	if (error == ERROR_PARSE_TOO_MANY)
		error_exit("Too many parameters");
	if (error == ERROR_DUPLICATE_AMBIANT)
		error_exit("Ambiant light already set");
	if (error == ERROR_DUPLICATE_CAM)
		error_exit("Camera already set");
	if (error == ERROR_PARSE_FOV)
		error_exit("Invalid FOV format");
	if (error == ERROR_PARSE_LINTESITY)
		error_exit("Invalid light intensity format");
}

void	parse_rgb(t_rgb *color, char *str_color)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str_color, ',');
	if (ft_tablen(rgb) != 3)
		parse_error_msg(ERROR_PARSE_TOO_MANY);
	i = -1;
	if (!ft_is_int_format(rgb[0]))
		parse_error_msg(ERROR_PARSE_RGB);
	color->r = ft_atoi(rgb[0]);
	if (color->r < 0 || color->r > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	if (!ft_is_int_format(rgb[1]))
		parse_error_msg(ERROR_PARSE_RGB);
	color->g = ft_atoi(rgb[1]);
	if (color->g < 0 || color->g > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	if (!ft_is_int_format(rgb[2]))
		parse_error_msg(ERROR_PARSE_RGB);
	color->b = ft_atoi(rgb[2]);
	if (color->b < 0 || color->b > 255)
		parse_error_msg(ERROR_PARSE_RGB);
	free_double_char(rgb);
}

void	parse_position(t_vector *vector, char *str_pos)
{
	char	**xyz;

	xyz = ft_split(str_pos, ',');
	if (ft_tablen(xyz) != 3)
		parse_error_msg(ERROR_PARSE_TOO_MANY);
	if (!ft_is_float_format(xyz[0]))
		parse_error_msg(ERROR_PARSE_POS);
	vector->x = ft_atoldb(xyz[0]);
	if (!ft_is_float_format(xyz[1]))
		parse_error_msg(ERROR_PARSE_POS);
	vector->y = ft_atoldb(xyz[1]);
	if (!ft_is_float_format(xyz[2]))
		parse_error_msg(ERROR_PARSE_POS);
	vector->z = ft_atoldb(xyz[2]);
	free_double_char(xyz);
}

void	parse_rotation(t_vector *vector, char *str_rot)
{
	char	**xyz;

	xyz = ft_split(str_rot, ',');
	if (ft_tablen(xyz) != 3)
		parse_error_msg(ERROR_PARSE_TOO_MANY);
	if (!ft_is_float_format(xyz[0]))
		parse_error_msg(ERROR_PARSE_ROT);
	vector->x = ft_atoldb(xyz[0]);
	if (vector->x > 1 || vector->x < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	if (!ft_is_float_format(xyz[1]))
		parse_error_msg(ERROR_PARSE_ROT);
	vector->y = ft_atoldb(xyz[1]);
	if (vector->y > 1 || vector->y < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	if (!ft_is_float_format(xyz[2]))
		parse_error_msg(ERROR_PARSE_ROT);
	vector->z = ft_atoldb(xyz[2]);
	if (vector->z > 1 || vector->z < -1)
		parse_error_msg(ERROR_PARSE_ROT);
	free_double_char(xyz);
	vector_normalizer(vector);
}
