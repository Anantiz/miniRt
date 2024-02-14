/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_double_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:09:44 by aurban            #+#    #+#             */
/*   Updated: 2024/01/19 18:01:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_double_char(char **cc)
{
	char	**ret;
	size_t	i;

	if (!cc)
		return (NULL);
	i = 0;
	while (cc[i])
		i++;
	ret = our_malloc(sizeof(char *) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (cc[i])
	{
		ret[i] = ft_strdup(cc[i]);
		if (!ret[i])
			return (free_double_char(ret), NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
