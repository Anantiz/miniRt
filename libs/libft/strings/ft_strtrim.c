/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:58:35 by aurban            #+#    #+#             */
/*   Updated: 2023/10/25 10:03:09 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	in_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (c);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	head_trim;
	size_t	tail_trim;
	size_t	trimmed_size;

	if (!s1)
		return (NULL);
	head_trim = 0;
	tail_trim = ft_strlen(s1) - 1;
	while (s1[head_trim] && in_set(set, s1[head_trim]))
		head_trim++;
	while (tail_trim > 0 && in_set(set, s1[tail_trim]))
		tail_trim--;
	trimmed_size = tail_trim - head_trim + 2;
	if (tail_trim == 0)
		trimmed_size = 1;
	trimmed = ft_calloc(trimmed_size, sizeof(char));
	if (trimmed != NULL)
		ft_strlcpy(trimmed, s1 + head_trim, trimmed_size);
	if (trimmed != NULL)
		return (trimmed);
	return (NULL);
}
