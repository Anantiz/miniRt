/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:56:28 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 17:41:51 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_decount;
	char	*s;
	char	*dest;
	size_t	dst_size;

	dest = dst;
	size_decount = size;
	s = (char *)src;
	while (size_decount-- != 0 && *dst)
		dst++;
	dst_size = (dst - dest);
	size_decount = size - dst_size;
	if (size_decount == 0)
		return (dst_size + ft_strlen(src));
	while (*s)
	{
		if (size_decount != 1)
		{
			*dst++ = *s;
			size_decount--;
		}
		s++;
	}
	*dst = '\0';
	return (dst_size + (s - src));
}
