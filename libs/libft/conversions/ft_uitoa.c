/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 02:34:11 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 15:07:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_buffer(char *buff, unsigned int n)
{
	if (n > 9)
		fill_buffer(buff - 1, n / 10);
	*buff = (n % 10) + '0';
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int	ncpy;
	char			*buffer;
	int				buff_size;

	ncpy = n;
	buff_size = 0;
	if (n == 0)
		buff_size++;
	while (ncpy)
	{
		buff_size++;
		ncpy /= 10;
	}
	buffer = our_malloc(buff_size + 1);
	if (!buffer)
		return (NULL);
	fill_buffer(buffer + buff_size - 1, n);
	buffer[buff_size] = '\0';
	return (buffer);
}
