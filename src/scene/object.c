/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:23:47 by aurban            #+#    #+#             */
/*   Updated: 2024/02/24 16:23:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	*new_object(t_vector *origin)
{
	t_object	*object;

	object = our_malloc(sizeof(t_object));

	return (object);
}
