/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:56:07 by aurban            #+#    #+#             */
/*   Updated: 2023/10/23 16:29:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = dst;
	source = src;
	if (dest < source)
	{
		i = 0;
		while (i < n)
		{
			dest[i] = source[i];
			i++;
		}
		return (dest);
	}
	while (n > 0)
	{
		dest[n - 1] = source[n - 1];
		n--;
	}
	return (dst);
}
