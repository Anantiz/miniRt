/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:54:26 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 19:14:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1000);
	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i])
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

/*
 input must be null terminated
 returns 0 if the strings are identical
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1000);
	i = 0;
	while (s1[i] == s2[i])
	{
		i++;
		if (!s1[i] || !s2[i])
			break ;
	}
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}
