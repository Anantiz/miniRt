/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:14:53 by aurban            #+#    #+#             */
/*   Updated: 2024/02/26 13:22:09 by aurban           ###   ########.fr       */
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
	pr_params = our_malloc(sizeof(char *) * 3);
	// Somewhat useless, since params is only 2 elements long anyway
	// at least it won't backfire if we change the format
	pr_params[0] = params[0];
	pr_params[1] = params[1];
	pr_params[2] = NULL;
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
