/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:50:25 by aurban            #+#    #+#             */
/*   Updated: 2024/02/07 10:48:17 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Allocates memory for a copy of s1, does the copy, returns the copy
*/
char	*ft_strdup(const char *s)
{
	char	*duplicate_str;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	duplicate_str = our_malloc(len + 1);
	if (duplicate_str == NULL)
		return (NULL);
	ft_strlcpy(duplicate_str, s, len + 1);
	return (duplicate_str);
}

/*
	Replaces the content of old with new
	free content of old
*/
void	ft_replace_str(char **old, char *new)
{
	our_free(*old);
	*old = new;
}

/*
	Replaces the content of old with a copy of new
	free content of old
*/
void	ft_replace_dupstr(char **old, char *new)
{
	our_free(*old);
	*old = ft_strdup(new);
}
