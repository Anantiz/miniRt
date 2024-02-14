/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 02:10:09 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 15:07:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	to_base(int c)
{
	if (c < 10)
		return ((char)(c + '0'));
	else
		return ((char)(c + 'a' - 10));
}

static void	fill_buffer_neg(long n, char *buffer)
{
	if (n < -15)
		fill_buffer_neg(n / 16, buffer - 1);
	else
		*(buffer - 1) = '-';
	*buffer = to_base((16 - (n % 16)) % 16);
}

static void	fill_buffer(long n, char *buffer)
{
	if (n > 15)
		fill_buffer(n / 16, buffer - 1);
	*buffer = to_base(n % 16);
}

char	*ft_ltohex(long n)
{
	long	ncpy;
	char	*buffer;
	int		digits;

	ncpy = n;
	digits = 0;
	if (n == 0)
		digits++;
	while (ncpy)
	{
		digits++;
		ncpy /= 16;
	}
	if (n < 0)
		digits++;
	buffer = our_malloc(sizeof(char) * (digits + 1));
	if (!buffer)
		return (NULL);
	if (n >= 0)
		fill_buffer(n, buffer + digits - 1);
	else
		fill_buffer_neg(n, buffer + digits - 1);
	buffer[digits] = '\0';
	return (buffer);
}

char	*ft_ltohex_up(long n)
{
	char	*str;
	int		i;

	str = ft_ltohex(n);
	if (!str)
		return (str);
	i = 0;
	while (str[i])
	{
		if (str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;
		i++;
	}
	return (str);
}
