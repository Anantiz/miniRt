/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:35:02 by aurban            #+#    #+#             */
/*   Updated: 2024/01/12 15:07:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* INTS*/

t_nodeint	*ft_llint_data_add_back(t_llint *list, long data, size_t index)
{
	t_nodeint	*node;

	if (!list)
		return (NULL);
	node = our_malloc(sizeof(t_nodeint));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = index;
	node->next = NULL;
	if (list->last)
	{
		node->previous = list->last;
		list->last->next = node;
	}
	else
		node->previous = NULL;
	list->last = node;
	list->size++;
	if (list->head == NULL)
		list->head = node;
	return (node);
}

t_nodeint	*ft_llint_data_add_front(t_llint *list, long data, size_t index)
{
	t_nodeint	*node;

	if (!list)
		return (NULL);
	node = our_malloc(sizeof(t_nodeint));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = index;
	node->next = list->head;
	if (list->head != NULL)
		list->head->previous = node;
	if (list->last == NULL)
		list->last = node;
	list->head = node;
	node->previous = NULL;
	list->size++;
	return (node);
}

/* STRINGS */

t_nodestr	*ft_llstr_add_back(t_llstr *list, char *data)
{
	t_nodestr	*node;

	if (!list)
		return (NULL);
	node = our_malloc(sizeof(t_nodestr));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = list->size;
	node->next = NULL;
	if (list->last)
	{
		node->previous = list->last;
		list->last->next = node;
	}
	else
		node->previous = NULL;
	list->last = node;
	list->size++;
	if (list->head == NULL)
		list->head = node;
	return (node);
}

t_nodestr	*ft_llstr_add_front(t_llstr *list, char *data)
{
	t_nodestr	*node;

	if (!list)
		return (NULL);
	node = our_malloc(sizeof(t_nodestr));
	if (!node)
		return (NULL);
	node->data = data;
	node->index = list->size;
	node->next = list->head;
	if (list->head != NULL)
		list->head->previous = node;
	if (list->last == NULL)
		list->last = node;
	list->head = node;
	node->previous = NULL;
	list->size++;
	return (node);
}
