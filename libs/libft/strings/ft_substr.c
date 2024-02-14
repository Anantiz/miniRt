/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:19:49 by aurban            #+#    #+#             */
/*   Updated: 2024/01/20 14:21:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strndup(const char *s, size_t len)
{
	char	*new_str;

	new_str = our_malloc((len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s, len + 1);
	return (new_str);
}

/*
	Creates a substring from s, starting at start, and len characters long
	Returns an empty string for Error
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*end_ptr;

	if (!s)
		return (ft_strdup(""));
	end_ptr = (char *)s;
	while (*end_ptr)
		end_ptr++;
	if (end_ptr - start < s)
		return (ft_strdup(""));
	if (len > (size_t)(end_ptr - (s + start)))
		len = end_ptr - (s + start);
	return (ft_strndup(s + start, len));
}
