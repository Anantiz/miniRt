/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:10:35 by aurban            #+#    #+#             */
/*   Updated: 2024/02/26 02:17:45 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

// Format: "cylinder", pos"x,y,z", ort"x,y,z" "d", "h", rgb

t_csg	*obj_new_cylinder(t_object *obj, char **params)
{
	(void)obj;
	return (pr_new_cylinder(params));
}
