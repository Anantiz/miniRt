/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:10:35 by aurban            #+#    #+#             */
/*   Updated: 2024/02/29 10:22:06 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

// Format: "cylinder", pos"x,y,z", ort"x,y,z" "d", "h", rgb

t_csg	*obj_new_cylinder(t_object *obj, char **params)
{
	t_csg	*cylinder;
	char	**pr_params;

	if (ft_strslen(params) < 3)
		return (NULL); // could also error_exit("Cylinder: wrong number of parameters");
	pr_params = our_malloc(sizeof(char *) * 5);
	pr_params[0] = params[0];
	pr_params[1] = params[1];
	pr_params[2] = params[2];
	if (params[3])
		pr_params[3] = params[3];
	else
		pr_params[3] = NULL;
	if (params[4])
		pr_params[4] = params[4];
	else
		pr_params[4] = NULL;
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
