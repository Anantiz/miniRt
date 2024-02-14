/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:04:58 by aurban            #+#    #+#             */
/*   Updated: 2024/01/26 11:56:54 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
exit(1) if any malloc fails
Safe against double free

action >=  1 -> SAFE_MALLOC_ALLOC
action  =  0 -> SAFE_MALLOC_FREE
action <= -1 -> SAFE_MALLOC_FREE_ALL

Not thread safe, If we ever use threads add a mutex here,
it would be a Giga bottleneck tho
*/
void	*safe_as_fuck_malloc(size_t bytes, void *address, int action)
{
	static t_mem_mng	*all_mallocs = NULL;
	t_mem_mng			*new_node;

	if (action > 0)
	{
		new_node = mem_manager_new_node(bytes, &action);
		if (action == -1)
		{
			mem_manager_del_list(&all_mallocs);
			perror("Critical memory failure during allocation");
			exit(1);
		}
		mem_manager_add_front(&all_mallocs, new_node);
	}
	else if (action == 0)
	{
		mem_manager_del_node(&all_mallocs, address);
		return (NULL);
	}
	else
	{
		mem_manager_del_list(&all_mallocs);
		return (NULL);
	}
	return (new_node->addr);
}

void	*our_malloc(size_t bytes)
{
	void	*ret;

	ret = safe_as_fuck_malloc(bytes, NULL, SAFE_MALLOC_ALLOC);
	return (ret);
}

void	our_free(void *address)
{
	if (address == NULL)
		return ;
	safe_as_fuck_malloc(0, address, SAFE_MALLOC_FREE);
}

void	error_exit(const char *error)
{
	ft_fprintf(2, "\033[31m🚨%s🚨\033[31m\n", error);
	exit(EXIT_FAILURE);
}
