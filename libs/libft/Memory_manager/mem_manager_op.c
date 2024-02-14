/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:11:58 by aurban            #+#    #+#             */
/*   Updated: 2024/01/29 10:10:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	mem_manager_add_front(t_mem_mng **head_, t_mem_mng *node)
{
	node->next = *head_;
	*head_ = node;
}

t_mem_mng	*mem_manager_new_node(size_t bytes, int *error)
{
	t_mem_mng	*node;

	*error = 0;
	node = malloc(sizeof(t_mem_mng));
	if (!node)
	{
		*error = -1;
		return (NULL);
	}
	node->addr = malloc(bytes);
	if (!node->addr)
	{
		*error = -1;
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

void	mem_manager_del_node(t_mem_mng **root, void *address)
{
	t_mem_mng	*prev;
	t_mem_mng	*node;

	if (!address)
		return ;
	node = *root;
	prev = NULL;
	while (node && node->addr != address)
	{
		prev = node;
		node = node->next;
	}
	if (prev && node != NULL)
		prev->next = node->next;
	if (node == *root)
		*root = (*root)->next;
	if (node != NULL)
		free(node->addr);
	free(node);
}

void	mem_manager_del_list(t_mem_mng **root)
{
	t_mem_mng	*node;
	t_mem_mng	*temp;

	if (!root)
		return ;
	node = *root;
	while (node)
	{
		temp = node->next;
		free(node->addr);
		free(node);
		node = temp;
	}
	*root = NULL;
}
