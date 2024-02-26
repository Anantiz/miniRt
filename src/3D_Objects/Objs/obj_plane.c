/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 02:08:03 by aurban            #+#    #+#             */
/*   Updated: 2024/02/26 02:17:53 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

t_csg	*obj_new_plane(t_object *obj, char **params)
{
	(void)obj;
	return (pr_new_cylinder(params));
}
