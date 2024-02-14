/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:55:32 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 09:30:02 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, char val, size_t n)
{
	char	*target;
	size_t	i;

	i = 0;
	target = s;
	while (i < n)
	{
		target[i] = val;
		i++;
	}
	return (target);
}

void	*ft_memset_int(void *s, int val, size_t n)
{
	int		*target;
	size_t	i;

	i = 0;
	target = (int *)s;
	while (i < n)
	{
		target[i] = val;
		i++;
	}
	return (target);
}
