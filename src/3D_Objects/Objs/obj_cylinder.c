/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:10:35 by aurban            #+#    #+#             */
/*   Updated: 2024/03/07 13:18:55 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"


/*
pos"x,y,z", dir"x,y,z" (OPTIONALL)
Format:  "diameter", "height", rgb
*/
t_csg	*obj_new_cylinder(t_object *obj, char **params)
{
	t_csg	*cylinder;
	char	**pr_params;

	if (ft_strslen(params) != 3)
		return (NULL); // could also error_exit("Cylinder: wrong number of parameters");
	pr_params = our_malloc(sizeof(char *) * 6);
	pr_params[0] = "0,0,0"; //relative  pos
	pr_params[1] = "0,0,0"; //relative  dir
	pr_params[2] = params[0];// diameter
	pr_params[3] = params[1];// height
	pr_params[4] = params[2];// color
	pr_params[5] = NULL;
	cylinder = pr_new_cylinder(pr_params);
	our_free(pr_params);

	printf("cylinder created\n");
	printf("cylinder radius: %f\n", cylinder->l->shape.cylinder.rad);
	printf("cylinder relative position: ");
	print_vector(&cylinder->l->pos);
	printf("cylinder absolute position: ");
	print_vector(add_vector(&obj->pos, &cylinder->l->pos));
	printf("cylinder color: ");
	print_rgb(&cylinder->l->rgb);
	printf("\n\n");
	return (pr_new_cylinder(params));
}
