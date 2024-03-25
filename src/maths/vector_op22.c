/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op22.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:34:48 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 19:40:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

inline t_vector	vadd(t_vector *v1, t_vector *v2)
{
	return ((t_vector){v1->x + v2->x, v1->y + v2->y, v1->z + v2->z});
}

inline t_vector	vsub(t_vector *v1, t_vector *v2)
{
	return ((t_vector){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z});
}

inline t_vector	vmult(t_vector *v1, double k)
{
	return ((t_vector){v1->x * k, v1->y * k, v1->z * k});
}

inline t_vector	vdiv(t_vector *v1, double k)
{
	return ((t_vector){v1->x / k, v1->y / k, v1->z / k});
}