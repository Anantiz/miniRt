/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:03:10 by aurban            #+#    #+#             */
/*   Updated: 2024/03/10 18:23:13 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char *s, long long int *i, size_t *j)
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
		while (ft_isspace(s[head]))
		{
			tail++;
			head++;
		}
		while (s[head] && !ft_isspace(s[head]))
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

/*
	Just like a split, separatos are from ft_isspace
*/
char	**ft_split_spaces(const char *s)
{
	char		**strs;
	size_t		count;
	size_t		j;
	long long	i;

	count = count_words((char *)s, &i, &j);
	strs = ft_calloc((count + 1), sizeof(char *));
	if (strs == NULL)
		return (NULL);
	while (j != count)
	{
		i = 0;
		while (ft_isspace(*s))
			s++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
		if (i != 0)
		{
			strs[j++] = ft_substr(s, 0, i);
			if (check_error(strs, j))
				return (NULL);
			s += i;
		}
	}
	return (strs);
}
