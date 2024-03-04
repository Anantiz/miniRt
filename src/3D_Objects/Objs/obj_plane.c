/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/04 13:54:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Format: "plane", pos"x,y,z", ort"x,y,z", rgb
*/
t_csg	*obj_new_plane(t_object *obj, char **params)
{
	t_csg	*plane;
	// static t_vector	plane_orientation[2] = { //WRONG
	// 	(t_vector){3, 2, 1},
	// 	(t_vector){1, 2, 3}
	// };

	if (!params || !params[0])
		error_exit("Plane: wrong number of parameters");
	plane = pr_new_plane(params[0]);
	// if (vec_dot_product(&obj->ort, &plane_orientation[0]) == 0) //WRONG
	// 	plane->l->shape.plane.norm = produit_vectoriel(&obj->ort, &plane_orientation[1]);
	// else //WRONG
	// 	plane->l->shape.plane.norm = produit_vectoriel(&obj->ort, &plane_orientation[0]);
	// vector_normalizer(plane->l->shape.plane.norm);
	// plane->l->shape.plane.norm->x = fabs(plane->l->shape.plane.norm->x);
	// plane->l->shape.plane.norm->y = fabs(plane->l->shape.plane.norm->y);
	// plane->l->shape.plane.norm->z = fabs(plane->l->shape.plane.norm->z);
	printf("Plane created\n");
	printf("Plane Orientation: ");
	print_vector(&obj->ort);
	// printf("Plane Normal:      ");
	// print_vector(plane->l->shape.plane.norm);
	printf("Plane color: ");
	print_rgb(&plane->l->rgb);
	printf("\n\n");
	return (plane);
}
