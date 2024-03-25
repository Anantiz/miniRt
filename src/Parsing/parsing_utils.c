/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:57:45 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

static char *parse_error_msg2(int error)
{
	if (error == ERROR_DUPLICATE_CAM)
		return (ft_strdup("Camera already set"));
	else if (error == ERROR_PARSE_FOV)
		return (ft_strdup("Invalid FOV format"));
	else if (error == ERROR_PARSE_LINTESITY)
		return (ft_strdup("Invalid light intensity format"));
	else if (error == ERROR_PARSE_INT)
		return (("Invalid integer format"));
	else if (error == ERROR_PARSE_FLOAT)
		return (ft_strdup("Invalid double format"));
	else if (error == ERROR_PARSE_WRONG_COUNT)
		return (ft_strdup("Wrong parameters count"));
	else if (error == ERROR_DUPLICATE_AMBIANT)
		return (ft_strdup("Ambiant light already set"));
	else
		return (ft_strdup("Unknown error"));
}

/*
It's so stupid instead of passing an int to then find a string
I could just send the string directly.

This code is embarassing , please spank me ( ͡° ͜ʖ ͡°)
*/
void	parse_error_msg(int error, char *custom_str)
{
	size_t	len;
	size_t	i;
	char	*str;

	if (error == ERROR_PARSE_RGB)
		str = ft_strdup("Invalid color format");
	else if (error == ERROR_PARSE_POS)
		str = ft_strdup("Invalid position format");
	else if (error == ERROR_PARSE_ROT)
		str = ft_strdup("Invalid orientation format");
	else
		str = parse_error_msg2(error);
	if (custom_str)
		str = ft_strjoin(ft_strjoin(str, " : "), custom_str);
	len = ft_strlen(str) + 16;
	printf("\033[1;31m");
	i = 0;
	while (i++ < len)
		printf("*");
	printf("\n Error: ***\033[0m %s \033[1;31m***\n", str);
	while (i-- != 1)
		printf("*");
	printf("\033[0m\n");
}

bool	parse_double(char *str, double *res)
{
	if (!ft_is_float_format(str))
	{
		printf("Invalid double: %s\n", str);
		parse_error_msg(ERROR_PARSE_FLOAT, NULL);
		return (false);
	}
	*res = ft_atoldb(str);
	return (true);
}

// Cuz I don't wanna do an other file just for this

bool	parse_int(char *str, int *res)
{
	int	valid;

	valid = 1;
	if (!ft_is_int_format(str))
	{
		printf("Invalid integer: %s\n", str);
		parse_error_msg(ERROR_PARSE_INT, NULL);
	}
	*res = ft_atoll_safe(str, INT_MAX, &valid);
	if (!valid)
		return (false);
	return (true);
}
