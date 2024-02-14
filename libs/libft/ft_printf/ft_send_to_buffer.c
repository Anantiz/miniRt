/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send_to_buff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 02:27:45 by aurban            #+#    #+#             */
/*   Updated: 2023/10/29 02:59:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Flushes the buffer to the file descriptor and update t_buffer_data
*/
void	ft_flush(char *buffer, t_bd *bd)
{
	bd->written += bd->offset;
	if (bd->error > -1)
		bd->error = write(bd->fd, buffer, bd->offset);
	ft_bzero(buffer, bd->offset);
	bd->offset = 0;
}

static void	printf_send_hexa(char *buff, t_bd *bd, unsigned int n, char c)
{
	char	*str;

	if (c == 'x')
	{
		str = ft_uitohex(n);
		ft_send_str(buff, bd, str);
		our_free(str);
	}
	else if (c == 'X')
	{
		str = ft_uitohex_up(n);
		ft_send_str(buff, bd, str);
		our_free(str);
	}
}

/*
This atrocity uses if statments because switch are apparently
to cool to be used		:(			*sobbing noises*
*/
int	ft_arg_to_buffer(char *buff, t_bd *bd, va_list *args, char c)
{
	if (c == 'c')
		ft_send_char(buff, bd, va_arg(*args, int));
	else if (c == 's')
		ft_send_str(buff, bd, va_arg(*args, char *));
	else if (c == 'p')
		ft_send_ptr(buff, bd, va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		ft_send_decimal(buff, bd, va_arg(*args, int));
	else if (c == 'u')
		ft_send_uint(buff, bd, va_arg(*args, int));
	else if (c == 'x' || c == 'X')
		printf_send_hexa(buff, bd, va_arg(*args, unsigned int), c);
	else if (c == '%')
		ft_send_char(buff, bd, '%');
	else if (c == 'l')
		ft_send_decimal(buff, bd, va_arg(*args, long));
	else
		return (-1);
	return (0);
}
