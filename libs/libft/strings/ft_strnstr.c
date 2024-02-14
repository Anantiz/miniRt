/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:14:35 by aurban            #+#    #+#             */
/*   Updated: 2023/11/17 14:45:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_lil(char *big, char *little, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && big[i] == little[i] && big[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *big_, const char *little, size_t len)
{
	size_t	little_len;
	char	*big;

	big = (char *)big_;
	if (!(*little))
		return (big);
	little_len = ft_strlen(little);
	while (*big && len > 0)
	{
		if (is_lil(big, (char *)little, len) == little_len)
			return (big);
		big++;
		len--;
	}
	return (NULL);
}
