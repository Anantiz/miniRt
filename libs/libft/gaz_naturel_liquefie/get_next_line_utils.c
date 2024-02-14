/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:13:20 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 13:03:55 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*resize_line(char *s1, size_t added_size)
{
	char	*joined;
	size_t	i;
	size_t	j;
	size_t	joined_size;

	joined_size = 0;
	if (s1)
		while (s1[joined_size])
			joined_size++;
	joined_size += added_size;
	joined = our_malloc((joined_size + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[j])
			joined[i++] = s1[j++];
	}
	while (i <= joined_size)
		joined[i++] = '\0';
	if (s1)
		our_free(s1);
	return (joined);
}

ssize_t	gnl_refill_buff(int fd, char *buff)
{
	ssize_t	nread;

	nread = read(fd, buff, BUFFER_SIZE);
	if (nread >= 0)
		buff[nread] = '\0';
	else
		buff[0] = '\0';
	return (nread);
}

char	*gnl_get_buff(int fd, char **buffers_list)
{
	size_t	i;

	if (fd > MAX_FD_HANDLE || fd < 0)
		return (NULL);
	if (buffers_list[fd])
		return (buffers_list[fd]);
	buffers_list[fd] = our_malloc(BUFFER_SIZE + 1);
	if (!buffers_list[fd])
		return (NULL);
	i = 0;
	while (i <= BUFFER_SIZE)
		buffers_list[fd][i++] = '\0';
	return (buffers_list[fd]);
}

char	*str_nulltrim(char *str)
{
	size_t	i;
	char	*new_str;

	if (!str)
		return (str);
	i = 0;
	while (str[i])
		i++;
	new_str = our_malloc(sizeof(char) * (i + 1));
	if (!new_str)
		return (str);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	our_free(str);
	return (new_str);
}
