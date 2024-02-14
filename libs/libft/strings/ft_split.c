/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:47:13 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 16:57:27 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *s, char sep, long long int *i, size_t*j)
{
	size_t	count;
	size_t	tail;
	size_t	head;

	count = 0;
	head = 0;
	tail = 0;
	*i = 0;
	*j = 0;
	while (s && s[head])
	{
		while (s[head] == sep)
		{
			tail++;
			head++;
		}
		while (s[head] && s[head] != sep)
			head++;
		if (tail != head)
			count++;
		tail = head;
	}
	return (count);
}

static int	check_error(char **strs, size_t j)
{
	size_t	i;

	if (strs[j - 1] == NULL)
	{
		i = 0;
		while (i < j - 1)
			our_free(strs[i++]);
		our_free(strs);
		return (1);
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char		**strs;
	size_t		count;
	size_t		j;
	long long	i;

	count = count_words((char *)s, c, &i, &j);
	strs = ft_calloc((count + 1), sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (j != count)
	{
		if ((s[i] == c || s[i] == '\0') && s != NULL)
		{
			strs[j++] = ft_substr(s, 0, i++);
			if (check_error(strs, j))
				return (NULL);
			s += i;
			i = 0;
		}
		i++;
	}
	return (strs);
}
