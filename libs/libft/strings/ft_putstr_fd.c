/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:00:39 by aurban            #+#    #+#             */
/*   Updated: 2024/02/06 12:32:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (!s)
		return (-1);
	len = 0;
	while (s[len])
		len++;
	return (write(fd, s, len));
}
