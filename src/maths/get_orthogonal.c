/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orthogonal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:06:45 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 10:26:16 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "miniRt.h"

#define ORTH_BASES_LEN 6

void	vec_abs(t_vector *v)
{
	v->x = fabs(v->x);
	v->y = fabs(v->y);
	v->z = fabs(v->z);
}

/*
This function is used to get an orthogonal vector when only one is given

	Returns a malloced vector that is orthogonal to the given one
*/
t_vector	*vec_get_ortho(t_vector *v)
{
	static bool		initialized = false;
	t_vector		*norm; // The orthogonal vector
	int				i;

	// For some satanic reason, these works kinda randomly
	static t_vector	orthogonal_basis[ORTH_BASES_LEN] = {
		(t_vector){1, 0, 0},
		(t_vector){0, 1, 0},
		(t_vector){0, 0, 1}
	};

	i = 0;
	if (initialized == false)
	{
		while (i < ORTH_BASES_LEN)
			vec_normalize(&orthogonal_basis[i++]);
		initialized = true;
	}

	if (!v || (v->x == 0 && v->y == 0 && v->z == 0)) // Should never be happening because of architecture choices
		error_exit("get_orthogonal() l:47: NULL vector given, fix that before production");
	i = 0;
	norm = NULL;
	while (i < ORTH_BASES_LEN)
	{
		if (vec_dot_product(v, &orthogonal_basis[i]) == 0) // 0 means orthogonal so we return it
		{
			// Not sure if I should return the Cross product or just the orthogonal basis
			norm = vec_cpy(&orthogonal_basis[i]);
			break ;
		}
		i++;
	}
	if (!norm) // Mathematically impossible, but my code sucks :)
		error_exit("Math: wrong orientation, can't find normal");
	vec_abs(norm);
	vec_normalize(norm);
	return (norm);
}