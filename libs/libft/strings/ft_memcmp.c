/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:03:59 by aurban            #+#    #+#             */
/*   Updated: 2023/10/23 16:29:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*target1;
	const unsigned char	*target2;

	if (n == 0)
		return (0);
	target1 = (const unsigned char *) s1;
	target2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (target1[i] != target2[i])
			return ((int)(target1[i] - target2[i]));
		i++;
	}
	return (0);
}
