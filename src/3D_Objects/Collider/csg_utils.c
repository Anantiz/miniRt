/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:31:11 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 20:34:11 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_csg	*csg_new_union(void)
{
	t_csg	*new;

	new = our_malloc(sizeof(*new));
	new->type = UNION;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_csg	*csg_new_inter(void)
{
	t_csg	*new;

	new = our_malloc(sizeof(*new));
	new->type = INTER;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_csg	*csg_new_diff(void)
{
	t_csg	*new;

	new = our_malloc(sizeof(*new));
	new->type = DIFF;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
