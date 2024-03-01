/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/01 16:23:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
Format: "plane", pos"x,y,z", ort"x,y,z", rgb
*/
t_csg	*obj_new_plane(t_object *obj, char **params)
{
	t_csg	*plane;
	char	**pr_params;

	(void)obj;
	// for (int i = 0;params[i]; i++)
	// 	printf("obj_Plane params[%d]: %s\n", i, params[i]);
	if (!params || !params[0])
		error_exit("Plane: wrong number of parameters");
	pr_params = our_malloc(sizeof(char *) * 4);
	pr_params[0] = "0,0,0"; // Relative pos to the object
	pr_params[1] = "1,1,1"; // Relative orientation to the object
	pr_params[2] = params[0]; // Color
	pr_params[3] = NULL;
	plane = pr_new_plane(pr_params);
	// plane->l->pos.x = -plane->l->pos.x;
	// plane->l->pos.z = -plane->l->pos.z;
	our_free(pr_params);

	printf("Plane created\n");
	printf("Plane relative position: ");
	print_vector(&plane->l->pos);
	printf("Plane absolute position: ");
	print_vector(&obj->pos);
	printf("Plane color: ");
	print_rgb(&plane->l->rgb);
	printf("\n\n");
	return (plane);
}
