/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:42:06 by aurban            #+#    #+#             */
/*   Updated: 2024/02/26 01:00:44 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define RESIZE_CHUNK SBUFSIZ * 2

static void	move_index_to_front(char *buffer, size_t index)
{
	size_t	j;

	j = 0;
	if (buffer[index++] != '\0')
		while (index < BUFFER_SIZE && buffer[index])
			buffer[j++] = buffer[index++];
	buffer[j] = '\0';
}

static int	summon_resize(int i, int l_offst, char **buff, char **line)
{
	if ((i + l_offst) % RESIZE_CHUNK == 0)
	{
		*line = resize_line(*line, RESIZE_CHUNK);
		if (*line == NULL)
		{
			(*buff)[0] = '\0';
			return (-1);
		}
	}
	return (0);
}

int	gnl_copy_buffer(char **buff, char **line, size_t *i, size_t *l_offst)
{
	if (summon_resize(*i, *l_offst, buff, line) == -1)
		return (-1);
	while (*i < BUFFER_SIZE && (*buff)[*i] != '\0' && (*buff)[*i] != '\n')
	{
		if (summon_resize(*i, *l_offst, buff, line) == -1)
			return (-1);
		(*line)[*i + *l_offst] = (*buff)[*i];
		(*i)++;
	}
	if (*i < BUFFER_SIZE && ((*buff)[*i] == '\n' || (*buff)[*i] == '\0' ))
	{
		(*line)[*i + *l_offst] = (*buff)[*i];
		move_index_to_front((*buff), *i);
		if (*i != 0 && (*line)[*i] == '\0')
			return (0);
		else
			return (420);
	}
	return (0);
}

static char	*read_buffer(int fd, char *buff, char *line)
{
	size_t	i;
	size_t	l_offst;
	ssize_t nread;
	int		status;

	l_offst = 0;
	i = 0;
	while (1)
	{
		if (!buff[0] || (i == BUFFER_SIZE))
		{
			nread = gnl_refill_buff(fd, buff);
			if (nread < 0)
				return (our_free(line), NULL);
			else if (nread == 0)
				return (line);
		}
		i = 0;
		status = gnl_copy_buffer(&buff, &line, &i, &l_offst);
		if (status == -1)
			return (NULL);
		else if (status == 420)
			return (line);
		l_offst += i;
	}
}

/*
reset == TRUE
	Deletes the previous buffer associated to the fd and return;
*/
char	*get_next_line(int fd, int reset)
{
	static char	*buffers_list[MAX_FD_HANDLE];
	char		*line;
	char		*buff;

	if (reset)
	{
		our_free(gnl_get_buff(fd, buffers_list));
		buffers_list[fd] = NULL;
		return (NULL);
	}
	buff = gnl_get_buff(fd, buffers_list);
	if (!buff)
		return (NULL);
	line = read_buffer(fd, buff, NULL);
	if (line == NULL)
	{
		our_free(buffers_list[fd]);
		buffers_list[fd] = NULL;
		return (NULL);
	}
	return (str_nulltrim(line));
}
