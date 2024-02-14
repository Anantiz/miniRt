/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:25:58 by aurban            #+#    #+#             */
/*   Updated: 2023/10/23 16:29:21 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*target;

	target = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (target[i] == (unsigned char)c)
			return (&target[i]);
		i++;
	}
	return (NULL);
}
