/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:54:04 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 11:53:16 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*
	Rules for float format:
	- Can have a sigle sign at the beginning
	- Can have a single comma or dot
	- Can have any number of digits
*/
bool	ft_is_float_format(const char *str)
{
	bool	has_sign;

	has_sign = false;
	while (*str)
	{
		if ((*str == '-' || *str == '+'))
		{
			if (has_sign)
				return (false);
			has_sign = true;
		}
		else if (!ft_isdigit(*str) && *str != '.' && *str != ',')
			return (false);
		str++;
	}
}

/*
	Rules for int format:
	- Can have a sigle sign at the beginning
	- Can have any number of digits
*/
bool	ft_is_int_format(const char *str)
{
	bool	has_sign;

	has_sign = false;
	while (*str)
	{
		if ((*str == '-' || *str == '+'))
		{
			if (has_sign)
				return (false);
			has_sign = true;
		}
		else if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
