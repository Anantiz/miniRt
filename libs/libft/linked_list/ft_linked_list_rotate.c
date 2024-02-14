/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linked_list_rotate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:31:21 by aurban            #+#    #+#             */
/*   Updated: 2023/12/01 17:04:00 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_llint_rotate(t_llint *list)
{
	if ((!list || !list->last || !list->head) || list->size == 1)
		return ;
	list->last->next = list->head;
	list->head->previous = list->last;
	list->last = list->last->next;
	list->head = list->head->next;
	list->last->next = NULL;
	list->head->previous = NULL;
}

void	ft_llint_rotate_inverse(t_llint *list)
{
	if (!list || !list->last || !list->head)
		return ;
	list->head->previous = list->last;
	list->last->next = list->head;
	list->head = list->last;
	list->last = list->last->previous;
	list->last->next = NULL;
	list->head->previous = NULL;
}
