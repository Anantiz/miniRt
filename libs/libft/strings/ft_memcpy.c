/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:55:57 by aurban            #+#    #+#             */
/*   Updated: 2023/10/23 16:29:26 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	source = (unsigned char *) src;
	dest = (unsigned char *) dst;
	i = 0;
	while (n)
	{
		dest[i] = source[i];
		i++;
		n--;
	}
	return (dst);
}
