/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:00:17 by aurban            #+#    #+#             */
/*   Updated: 2024/03/16 12:23:08 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/*
	Project a onto b

	Formula:
	((a dot b) / (b dot b)) * b
*/
t_vector	*vec_project(t_vector *a, t_vector *b)
{
	t_vector	*ret;

	ret = vec_cpy(b);
	vec_normalize(ret);
	return (vec_realloc(&ret, \
	vec_mult(vec_dot_product(a, b) / vec_dot_product(b, b), ret)));
}
