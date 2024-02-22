/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:12:27 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/22 09:40:47 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

t_camera	*new_camera(t_vector *pos, t_vector *direction, float fov)
{
	t_camera	*camera;

	camera = our_malloc(sizeof(t_camera));
	camera->direction = direction;
	camera->pos = pos;
	camera->up = addition(pos, new_vector(0, 1, 0));
	camera->right = produit_vectoriel();
	camera->fov = fov;
	return (camera);
}