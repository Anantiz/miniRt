/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_to_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:06:49 by aurban            #+#    #+#             */
/*   Updated: 2024/01/22 16:57:27 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_send_char(char *buffer, t_bd *bd, char c)
{
	if (bd->offset == SBUFSIZ)
		ft_flush(buffer, bd);
	buffer[bd->offset++] = c;
	if (c == '\n')
		ft_flush(buffer, bd);
}

void	ft_send_str(char *buffer, t_bd *bd, const char *str)
{
	if (!str)
		str = (const char *)"(null)";
	while (*str)
	{
		if (bd->offset == SBUFSIZ)
		{
			ft_flush(buffer, bd);
			if (bd->error < 0)
				return ;
		}
		buffer[bd->offset++] = *str;
		if (*(str++) == '\n')
		{
			ft_flush(buffer, bd);
			if (bd->error < 0)
				return ;
		}
	}
}

void	ft_send_ptr(char *buffer, t_bd *bd, void *ptr)
{
	char	*str;

	ft_send_char(buffer, bd, '0');
	ft_send_char(buffer, bd, 'x');
	if (ptr == NULL)
	{
		ft_send_char(buffer, bd, '0');
		return ;
	}
	str = ft_ultohex((unsigned long) ptr);
	ft_send_str(buffer, bd, str);
	our_free(str);
}

void	ft_send_decimal(char *buffer, t_bd *bd, long long n)
{
	char	*n_str;

	n_str = ft_lltoa(n);
	ft_send_str(buffer, bd, n_str);
	our_free(n_str);
}

void	ft_send_uint(char *buffer, t_bd *bd, unsigned int n)
{
	char	*n_str;

	n_str = ft_uitoa(n);
	ft_send_str(buffer, bd, n_str);
	our_free(n_str);
}
