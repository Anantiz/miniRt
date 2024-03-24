/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:11:21 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

static void	debug_new_pl(t_leaf *pl)
{
	printf("Plane created\n");
	printf("\tPlane pos:  ");
	print_vector(&pl->pos);
	printf("\tPlane dir:  ");
	print_vector(&pl->dir);
	printf("\tPlane color:  ");
	print_rgb(&pl->rgb);
	printf("\n\n");
}

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
	t_csg		*plane;
	t_vector	*norm;

	if (ft_tablen(params) != 1)
		return (NULL);
	plane = pr_new_plane(params[0]);
	if (!plane)
		return (NULL);
	norm = vec_get_ortho(&obj->dir);
	plane->l->shape.plane.norm = *norm;
	our_free(norm);
	debug_new_pl(plane->l);
	return (plane);
}
