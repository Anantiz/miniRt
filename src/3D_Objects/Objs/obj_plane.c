/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/05 10:40:52 by aurban           ###   ########.fr       */
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

/*
Format: "plane", pos"x,y,z", ort"x,y,z", rgb
the first 3 params are already parsed in obj_new
params[0] is the color
*/
t_csg	*obj_new_plane(t_object *obj, char **params)
{
	t_csg	*plane;
	// Technically a const, but some functions don't like it
	// It's shared data for any plane, since the base is always the same
	static t_vector	orthogonal_basis[3] = {
		(t_vector){1, 0, 0},
		(t_vector){0, 1, 0},
		(t_vector){0, 0, 1}
	};

	if (!params || !params[0]) // The parsed map is wrong, we can't do anything
		error_exit("Plane: wrong number of parameters");
	plane = pr_new_plane(params[0]); // Will only parse the color, the rest is already done

	// We need to find the normal of the plane, since it will be used to calculate the intersection
	// Pre computing to avoid doing it at every intersection since it's constant
	if (vec_dot_product(&obj->dir, &orthogonal_basis[0]) == 0)
		plane->l->shape.plane.norm = &orthogonal_basis[0];
	else if (vec_dot_product(&obj->dir, &orthogonal_basis[1]) == 0)
		plane->l->shape.plane.norm = &orthogonal_basis[1];
	else if (vec_dot_product(&obj->dir, &orthogonal_basis[2]) == 0)
		plane->l->shape.plane.norm = &orthogonal_basis[2];
	else // This mathematically shouldn't happen, but we never know
		error_exit("Plane: wrong orientation, can't find normal");
	plane->l->shape.plane.norm->x = fabs(plane->l->shape.plane.norm->x);
	plane->l->shape.plane.norm->y = fabs(plane->l->shape.plane.norm->y);
	plane->l->shape.plane.norm->z = fabs(plane->l->shape.plane.norm->z);
	vector_normalizer(plane->l->shape.plane.norm);

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
