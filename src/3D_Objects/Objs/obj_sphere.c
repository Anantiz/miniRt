/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:14:53 by aurban            #+#    #+#             */
/*   Updated: 2024/02/29 14:49:32 by aurban           ###   ########.fr       */
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
	pr_params[0] = "1,1,1"; //relative  pos
	pr_params[1] = params[0];// size
	pr_params[2] = params[1];// color
	pr_params[3] = NULL;
	sphere = pr_new_sphere(pr_params);
	our_free(pr_params);


	printf("Sphere created\n");
	printf("Sphere radius: %f\n", sphere->l->shape.sphere.rad);
	printf("Sphere relative position: ");
	print_vector(&sphere->l->pos);
	printf("Sphere absolute position: ");
	print_vector(add_vector(&obj->pos, &sphere->l->pos));
	printf("Sphere color: ");
	print_rgb(&sphere->l->rgb);
	printf("\n\n");
	return (sphere);
}
