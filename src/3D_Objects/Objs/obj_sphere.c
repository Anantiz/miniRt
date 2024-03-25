/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:14:53 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 23:31:30 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

static void	debug_new_sp(t_leaf *sp)
{
	printf("Sphere created\n");
	printf("\tSphere pos:\t");
	print_vector(&sp->pos);
	printf("\tSphere radius: %f\n", sp->shape.sphere.r);
	printf("\tSphere color:  ");
	print_rgb(&sp->rgb);
	printf("\n\n");
}

// Format: X"sphere"X, Xpos"x,y,z"X, "d", rgb

t_csg	*obj_new_sphere(t_object *obj, char **params)
{
	t_csg		*sphere;
	char		**pr_params;

	pr_params = our_malloc(sizeof(char *) * 3);
	if (ft_strslen(params) != 2)
		return (NULL);
	pr_params[0] = params[0]; // size
	pr_params[1] = params[1]; // color
	pr_params[2] = NULL;
	sphere = pr_new_sphere((t_vector[2]){obj->pos, obj->dir}, pr_params);
	our_free(pr_params);
	if (!sphere)
		return (NULL);
	debug_new_sp(sphere->l);
	return (sphere);
}
