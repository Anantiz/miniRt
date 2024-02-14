/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:19:18 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 15:07:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lltoa_pos(char *buffer, int buffer_len, long long n)
{
	buffer[buffer_len--] = '\0';
	while (buffer_len >= 0)
	{
		buffer[buffer_len--] = (n % 10) + '0';
		n = n / 10;
	}
}

static void	ft_lltoa_neg(char *buffer, int buffer_len, long long n)
{
	buffer[buffer_len--] = '\0';
	buffer[0] = '-';
	while (buffer_len > 0)
	{
		buffer[buffer_len--] = ((10 - (n % 10)) % 10) + '0';
		n = n / 10;
	}
}

char	*ft_lltoa(long long n)
{
	char		*buffer;
	int			buffer_len;
	long long	ncpy;

	ncpy = n;
	buffer_len = 0;
	if (n <= 0)
		buffer_len++;
	while (n)
	{
		buffer_len++;
		n = n / 10;
	}
	buffer = our_malloc((buffer_len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (ncpy >= 0)
		ft_lltoa_pos(buffer, buffer_len, ncpy);
	else
		ft_lltoa_neg(buffer, buffer_len, ncpy);
	return (buffer);
}
