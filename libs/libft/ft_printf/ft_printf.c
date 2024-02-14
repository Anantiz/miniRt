/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:15:02 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 14:51:41 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	If the buffer is full, flush it to the file descriptor
	If new line, flush the buffer and send the new line
*/
static const char	*rf2(t_bd *bd, const char *s, char *buffer, va_list *args)
{
	if (bd->offset == SBUFSIZ)
		ft_flush(buffer, bd);
	if (*s == '\n')
	{
		buffer[bd->offset++] = *s;
		ft_flush(buffer, bd);
		return (s + 1);
	}
	if (bd->error < 0)
		return (NULL);
	else if (*s == '%')
	{
		s++;
		if (ft_arg_to_buffer(buffer, bd, args, *s) == -1)
		{
			bd->error = -1;
			return (NULL);
		}
	}
	else
		buffer[bd->offset++] = *s;
	return (s + 1);
}

/*
No check is made for the validity of va_arg
Make sure all the arguments are given in the right order
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_bd	bd;
	char	buffer[SBUFSIZ];

	if (!format)
		return (-1);
	ft_bzero(buffer, SBUFSIZ);
	va_start(args, format);
	bd.offset = 0;
	bd.written = 0;
	bd.error = 0;
	bd.fd = STDOUT_FILENO;
	while (*format)
	{
		format = rf2(&bd, format, buffer, &args);
		if (bd.error < 0)
			return (-1);
	}
	ft_flush(buffer, &bd);
	va_end(args);
	return (bd.written);
}

/*
No check is made for the validity of va_arg
Make sure all the arguments are given in the right order
*/
int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	t_bd	bd;
	char	buffer[SBUFSIZ];

	if (!format)
		return (-1);
	ft_bzero(buffer, SBUFSIZ);
	va_start(args, format);
	bd.offset = 0;
	bd.written = 0;
	bd.error = 0;
	bd.fd = fd;
	while (*format)
	{
		format = rf2(&bd, format, buffer, &args);
		if (bd.error < 0)
			return (-1);
	}
	ft_flush(buffer, &bd);
	va_end(args);
	return (bd.written);
}
