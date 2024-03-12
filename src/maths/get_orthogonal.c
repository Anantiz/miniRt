/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_orthogonal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:06:45 by aurban            #+#    #+#             */
/*   Updated: 2024/03/12 09:57:58 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "miniRt.h"

#define ORTH_BASES_LEN 4

/*
This function is used to get an orthogonal vector when only one is given

	Returns a malloced vector that is orthogonal to the given one
*/
t_vector	*vec_get_ortho(t_vector *v)
{
	t_vector		*norm; // The orthogonal vector
	int				i;

	// For some satanic reason, these works kinda randomly
	static t_vector	orthogonal_basis[ORTH_BASES_LEN] = {
		(t_vector){1, 0, 0},
		(t_vector){0, 1, 0},
		(t_vector){0, 0, 1},
	};

	// if ()
	// {
	// 	// Test if they are orthogonal
	// 	for (int i=0; i < ORTH_BASES_LEN; i++)
	// 	{
	// 		for (int j=0; j < ORTH_BASES_LEN; j++)
	// 		{
	// 				if (i != j && vec_dot_product(&orthogonal_basis[i], &orthogonal_basis[j]) != 0)
	// 				{
	// 					printf("\033[31mOrthogonal basis not orthogonal\033[0m\n");
	// 					printf("i: %d, j: %d\n", i, j);
	// 					printf("Dot product: %f\n", vec_dot_product(&orthogonal_basis[i], &orthogonal_basis[j]));
	// 					print_vector(&orthogonal_basis[i]);
	// 					print_vector(&orthogonal_basis[j]);
	// 					printf("\n");
	// 				}
	// 		}

	// 	}
	// }

	if (!v || (v->x == 0 && v->y == 0 && v->z == 0)) // Should never be happening because of architecture choices
		error_exit("get_orthogonal() l:47: NULL vector given, fix that before production");
	i = 0;
	norm = NULL;
	while (i < ORTH_BASES_LEN)
	{
		// The cross product will be orthogonal to the given vector if they are not parallel
		if (fabs(vec_dot_product(v, &orthogonal_basis[i])) != 1)
		{
			norm = vec_cross_product(v, &orthogonal_basis[i]);
			break ;
		}
		i++;
	}
	if (!norm) // Mathematically impossible, but my code sucks :) , here to debug
		error_exit("Math: wrong orientation, can't find normal");
	vec_normalize(norm);
	return (norm);
}
