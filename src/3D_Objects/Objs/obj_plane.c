/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/05 16:43:36 by aurban           ###   ########.fr       */
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
#define OBJPLBL 6

t_vector	*get_plane_norm(t_vector *plane_dir)
{
	// For some satanic reason, these works kinda randomly
	static t_vector	orthogonal_basis[OBJPLBL] = {
		(t_vector){1, 1, 0},
		(t_vector){0, 1, 1},
		(t_vector){1, 0, 1},
		(t_vector){1, 0, 0},
		(t_vector){0, 1, 0},
		(t_vector){0, 0, 1},
	};
	t_vector		*norm;
	int				i;

	i = 0;
	while (i < OBJPLBL)// We normalize the base, unoptimized code
		vector_normalizer(&orthogonal_basis[i++]);
	i = 0;
	norm = NULL;
	while (i < OBJPLBL)
	{
		if (vec_dot_product(plane_dir, &orthogonal_basis[i]) == 0)
		{
			norm = produit_vectoriel(plane_dir, &orthogonal_basis[i]);
			break ;
		}
		i++;
	}
	if (!norm) // What the hell is this plane orientation?
		error_exit("Plane: wrong orientation, can't find normal");
	norm->x = fabs(norm->x);
	norm->y = fabs(norm->y);
	norm->z = fabs(norm->z);
	vector_normalizer(norm);
	return (norm);
}

/*
Format: "plane", pos"x,y,z", ort"x,y,z", rgb
the first 3 params are already parsed in obj_new
params[0] is the color
*/
t_csg	*obj_new_plane(t_object *obj, char **params)
{
	t_csg	*plane;

	if (!params || !params[0]) // The parsed map is wrong, we can't do anything
		error_exit("Plane: wrong number of parameters");
	plane = pr_new_plane(params[0]); // Will only parse the color, the rest is already done
	plane->l->shape.plane.norm = get_plane_norm(&obj->dir);

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
