/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:29:11 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 14:04:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Returns a pointer to the first occurence of c in s
	Returns NULL if not found
*/
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
