/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:04:12 by aurban            #+#    #+#             */
/*   Updated: 2024/03/28 12:36:44 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

static void	debug_new_cn(t_leaf *cy)
{
	printf("Cone created\n");
	printf("\nCone pos:  ");
	print_vector((&cy->pos));
	printf("\tCone dir:  ");
	print_vector((&cy->dir));
	printf("\tCone radius:   %f\n", cy->shape.cylinder.r);
	printf("\tCone height:   %f\n", cy->shape.cylinder.h);
	printf("\tCone color:    ");
	print_rgb(&cy->rgb);

	printf("\n\n");
}

/*
Format:  "diameter", "height", rgb
*/
t_csg	*obj_new_cone(t_object *obj, char **params)
{
	t_csg	*cone;
	char	**pr_params;

	if (ft_strslen(params) != 3)
		return (NULL);
	pr_params = our_malloc(sizeof(char *) * 4);
	pr_params[0] = params[0];// diameter
	pr_params[1] = params[1];// height
	pr_params[2] = params[2];// color
	pr_params[3] = NULL;
	cone = pr_new_cone((t_vector[2]){obj->pos, obj->dir}, pr_params);
	our_free(pr_params);
	static const char		*shape_names[] = {"Sphere", "Plane", "Cylinder", "Cone"};
	printf("Collision Object: ");
	printf("%s\n", shape_names[cone->type]);
	if (!cone)
		return (NULL);
	debug_new_cn(cone->l);
	return (cone);
}
