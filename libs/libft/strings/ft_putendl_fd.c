/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:19:24 by aurban            #+#    #+#             */
/*   Updated: 2024/02/03 09:44:51 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	size_t	len;
	ssize_t	ret;

	if (!s)
		return (-1);
	len = ft_strlen(s);
	ret = write(fd, s, len);
	if (ret == -1)
		return (-1);
	return (write(fd, "\n", 1) + ret);
}
