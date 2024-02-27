/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:45:12 by aurban            #+#    #+#             */
/*   Updated: 2024/02/27 11:50:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Utility to manage file descriptors in case of error_exit
*/

#define GC_ADD_FD		1
#define GC_CLOSE_FD		2
#define CLOSE_ALL		3

static void	gd_fd_manager(int fd, int status)
{
	static int	fds[MAX_FD_HANDLE] = {-1};
	int			i;

	if (status == GC_ADD_FD)
	{
		fds[fd] = 1;
	}
	else if (status == GC_CLOSE_FD)
	{
		if (fds[fd])
		{
			close(fd);
			fds[fd] = -1;
		}
	}
	else if (status == CLOSE_ALL)
	{
		i = 0;
		while (i < MAX_FD_HANDLE)
		{
			if (fds[i] != -1)
				close(i);
			i++;
		}
	}
}

void	gc_add_fd(int fd)
{
	gd_fd_manager(fd, GC_ADD_FD);
}

void	gc_close_fd(int fd)
{
	gd_fd_manager(fd, GC_CLOSE_FD);
}

void	gc_close_all(void)
{
	gd_fd_manager(0, CLOSE_ALL);
}
