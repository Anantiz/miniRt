/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:00:17 by aurban            #+#    #+#             */
/*   Updated: 2024/03/15 13:13:57 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
	Returns the projection of projected onto axis

	Formula:
	((a dot b) / (b dot b)) * b
*/
t_vector	*vec_project(t_vector *axis, t_vector *projected)
{
	t_vector	*ret;

	ret = vec_cpy(axis);
	vec_normalize(ret);
	return (vec_realloc(&ret, vec_mult(vec_dot_product(axis, projected) \
			/ vec_dot_product(projected, projected), ret)));
}
