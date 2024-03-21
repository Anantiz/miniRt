/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orthogonal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:06:45 by aurban            #+#    #+#             */
/*   Updated: 2024/03/14 15:44:50 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "miniRt.h"

#define ORTH_BASES_LEN 3

/*
	Returns an orthogonal vector to the one given
*/
t_vector	*vec_get_ortho(t_vector *v)
{
	t_vector		*ret;
	int				i;

	static t_vector	basis[ORTH_BASES_LEN] = {
		(t_vector){1, 0, 0},
		(t_vector){0, 1, 0},
		(t_vector){0, 0, 1},
	};
	// Should never be happening because of architecture choices, so this is here to debug
	if (!v || (v->x == 0 && v->y == 0 && v->z == 0))
		error_exit("get_orthogonal() l:47: NULL vector given, fix that before production");
	i = 0;
	ret = NULL;
	while (i < ORTH_BASES_LEN)
	{
		if (fabs(vec_dot_product(v, &basis[i])) != 1)
		{
			ret = vec_cross_product(v, &basis[i]);
			break ;
		}
		i++;
	}
	if (!ret) // Mathematically impossible, but my code sucks :) , here to debug
		error_exit("Math: wrong orientation, can't find normal");
	return (ret);
}
