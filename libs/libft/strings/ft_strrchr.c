/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:37:08 by aurban            #+#    #+#             */
/*   Updated: 2023/10/20 14:27:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*last_occurence;

	len = ft_strlen(s);
	last_occurence = 0;
	i = 0;
	while (i < len + 1)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			last_occurence = (char *) &s[i];
		i++;
	}
	return (last_occurence);
}
