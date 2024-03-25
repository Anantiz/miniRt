/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_fighter_jet.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 08:25:18 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 23:03:31 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
	params[0] = Scale
	params[1] = main color
	params[2] = secondary color
	params[3] = tertiary color
*/
t_csg	*obj_new_fighter_jet(t_object *obj, char **params)
{
	t_csg	*root;

	(void)obj;
	(void)params;
	// For now just a simple diff test to check if the CSG works
	root = csg_new_diff();
	root->right = pr_new_cylinder((t_vector[]){{0,0,0}, {0,0,1}} ,(char*[]){"10", "40", "0,255,0"}); // Cut
	root->left = pr_new_cylinder((t_vector[]){{-30,0,0},{1,0,0}} , (char*[]){"20", "60", "255,255,255"}); // Visible
	return (root);
}
