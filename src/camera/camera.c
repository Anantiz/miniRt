/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:12:27 by lkary-po          #+#    #+#             */
/*   Updated: 2024/02/21 09:22:35 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

t_camera	*new_camera(t_vector *pos, t_vector *direction, t_vector *right, t_vector *up, float fov)
{
	t_camera	*camera;

	camera = our_malloc(sizeof(t_camera));
	camera->direction = direction;
	camera->pos = pos;
	camera->right = right;
	camera->up = up;
	camera->fov = fov;
	return (camera);
}