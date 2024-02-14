/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:03:52 by aurban            #+#    #+#             */
/*   Updated: 2024/02/07 10:47:58 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *nptr)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr && *nptr >= 48 && *nptr <= 57)
	{
		result *= 10;
		result += sign * (*nptr++ - 48);
	}
	return (result);
}

static int	check_overflow(long long result, long long add, \
long long max_value, int *valid)
{
	if (add >= 0)
	{
		if (result > (max_value / 10) || result > (max_value / 10) - add)
		{
			*valid = 0;
			return (1);
		}
	}
	else
	{
		if (result < ((-max_value - 1) / 10) || result < \
			((-max_value - 1) / 10) - add)
		{
			*valid = 0;
			return (1);
		}
	}
	return (0);
}

/*
	Perform an atoi, but with a max value.
	If the number is bigger than max_value:
		-`valid` is set to 0.
		- The (largest_value ± 9) reached before overflow is returned.
*/
long long	ft_atoll_safe(char *s, long long max_value, int *valid)
{
	long long	result;
	int			sign;

	*valid = 1;
	result = 0;
	sign = 1;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s && *s >= 48 && *s <= 57)
	{
		if (check_overflow(result, sign * (*s - 48), max_value, valid))
			return (result);
		result *= 10;
		result += sign * (*s++ - 48);
		if (result > max_value)
			return (max_value);
	}
	return (result);
}
