/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:53:49 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 16:24:01 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	print_vector(t_vector *vector)
{
	if (vector)
		printf(" %8.2f x, %8.2f y, %8.2f z\n", vector->z, vector->y, vector->x);
	else
		printf("NULL\n");
}

void	print_collision(t_collision *collision)
{
	static const char		*shape_names[] = {"Sphere", "Plane", "Cylinder"};

	if (collision)
	{
		printf("Collision Object: ");
		printf("%s\n", shape_names[collision->obj->type]);
		printf("Collision detected at distance: %8.2f\n", collision->dist);
		printf("Collision point: ");
		print_vector(&collision->point);
	}
	else
		printf("No collision detected\n");
	printf("\n");
}