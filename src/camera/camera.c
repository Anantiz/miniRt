/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:12:27 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/22 10:18:22 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

t_camera	*new_camera(t_vector *pos, t_vector *direction, float fov)
{
	t_camera	*camera;

	camera = our_malloc(sizeof(t_camera));
	camera->direction = vector_normalizer(direction);
	camera->pos = pos;
	camera->up = addition(pos, new_vector(0, 1, 0));
	camera->right = produit_vectoriel(camera->up, camera->direction);
	camera->fov = fov;
	return (camera);
}