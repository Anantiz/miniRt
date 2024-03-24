/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:10:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:41:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"


static void	debug_new_cy(t_leaf *cy)
{
	printf("Cylinder created\n");
	printf("\tCylinder pos:  ");
	print_vector((&cy->pos));
	printf("\tCylinder dir:  ");
	print_vector((&cy->dir));
	printf("\tCylinder radius:   %f\n", cy->shape.cylinder.r);
	printf("\tCylinder height:   %f\n", cy->shape.cylinder.h);
	printf("\tCylinder color:    ");
	print_rgb(&cy->rgb);
	printf("\n\n");
}

/*
pos"x,y,z", dir"x,y,z" (OPTIONALL)
Format:  "diameter", "height", rgb
*/
t_csg	*obj_new_cylinder(t_object *obj, char **params)
{
	t_csg	*cylinder;
	char	**pr_params;

	if (ft_strslen(params) != 3)
		return (NULL);
	pr_params = our_malloc(sizeof(char *) * 4);
	pr_params[0] = params[0];// diameter
	pr_params[1] = params[1];// height
	pr_params[2] = params[2];// color
	pr_params[3] = NULL;
	cylinder = pr_new_cylinder((t_vector[2]){obj->pos, obj->dir}, pr_params);
	our_free(pr_params);
	if (!cylinder)
		return (NULL);
	debug_new_cy(cylinder->l);
	return (cylinder);
}
