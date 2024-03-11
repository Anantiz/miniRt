/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 09:21:49 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
MEMO:

Dot product:
	If the dot product of two vectors is 0, it means they are orthogonal
	If the dot product of two vectors is 1, it means they are parallel

Cross product:
	If the two vectors are parallel, the cross product will be 0
	If the two vectors are orthogonal, the cross product will be the vector
		orthogonal to the two vectors (So the third vector of the base)
*/
// OBJect_PLane_Basis_Length

/*
Format: "plane", pos"x,y,z", ort"x,y,z", rgb
the first 3 params are already parsed in obj_new
params[0] is the color
*/
t_csg	*obj_new_plane(t_object *obj, char **params)
{
	t_csg	*plane;

	if (ft_tablen(params) != 1)
		error_exit("Plane: wrong number of parameters");
	// Will only parse the color, the rest is already done
	// It's just more consistent to have the same function signature
	plane = pr_new_plane(params[0]);
	plane->l->shape.plane.norm = vec_get_ortho(&obj->dir);

	// Debug
	printf("Plane created\n");
	printf("\tPlane position:    ");
	print_vector(&obj->pos);
	printf("\tPlane Orientation: ");
	print_vector(&obj->dir);
	printf("\tPlane Normal:      ");
	print_vector(plane->l->shape.plane.norm);
	printf("\tPlane color:       ");
	print_rgb(&plane->l->rgb);
	printf("\n\n");
	return (plane);
}
