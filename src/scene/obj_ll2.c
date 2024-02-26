/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ll2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:33:23 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 19:36:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_ll_obj	*tll_new_spot_node(t_spot_light *light)
{
	t_ll_obj	*node;

	node = our_malloc(sizeof(t_ll_obj));
	node->l = light;
	node->o = NULL;
	node->next = NULL;
	return (node);
}
