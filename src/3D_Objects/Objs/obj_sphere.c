/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:14:53 by aurban            #+#    #+#             */
/*   Updated: 2024/03/23 14:34:46 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

// Format: X"sphere"X, Xpos"x,y,z"X, "d", rgb

t_csg	*obj_new_sphere(t_object *obj, char **params)
{
	t_csg	*sphere;
	char	**pr_params;

	// Unused, but we might use it later, easier to remove than to add
	(void)obj;
	// for (int i = 0;params[i]; i++)
	// 	printf("Sphere params[%d]: %s\n", i, params[i]);
	pr_params = our_malloc(sizeof(char *) * 5);
	if (!params || !params[0] || !params[1])
		error_exit("Sphere: wrong number of parameters");
	pr_params[0] = "0,0,0"; //relative  pos
	pr_params[1] = params[0];// size
	pr_params[2] = params[1];// color
	pr_params[3] = NULL;
	sphere = pr_new_sphere(pr_params);
	our_free(pr_params);
	vec_add_inplace(&sphere->l->pos, &obj->pos);

	printf("Sphere created\n");
	printf("\tSphere radius:   %f\n", sphere->l->shape.sphere.r);
	printf("\tSphere color:    ");
	print_rgb(&sphere->l->rgb);
	printf("\tSphere pos:  ");
	print_vector(vec_add(&obj->pos, &sphere->l->pos));
	printf("\n\n");
	return (sphere);
}
