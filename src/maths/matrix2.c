/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:30:01 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 19:47:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*Rotate arround X axis*/
t_vector	mtx_rotate_x(t_vector *v, float angle)
{
	t_vector	new;

	new.x = v->x;
	new.y = v->y * cosf(angle) - v->z * sinf(angle);
	new.z = v->y * sinf(angle) + v->z * cosf(angle);
	return (new);
}

/*Rotate arround Y axis*/
t_vector	mtx_rotate_y(t_vector *v, float angle)
{
	t_vector	new;

	new.x = v->x * cosf(angle) + v->z * sinf(angle);
	new.y = v->y;
	new.z = -v->x * sinf(angle) + v->z * cosf(angle);
	return (new);
}

/*Rotate arround Z axis*/
t_vector	mtx_rotate_z(t_vector *v, float angle)
{
	t_vector	new;

	new.x = v->x * cosf(angle) - v->y * sinf(angle);
	new.y = v->x * sinf(angle) + v->y * cosf(angle);
	new.z = v->z;
	return (new);
}
