/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_norm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:21:42 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 12:07:02 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

// static t_vector	*light_get_norm(t_collision *collision, t_e_prim type)
// {
// 	t_vector	*norm;
// 	t_vector	*tmp;

// 	if (type == PLANE)
// 	{
// 		// It is pre-computed
// 		return (collision->obj->l->shape.plane.norm);
// 	}
// 	else if (type == SPHERE)
// 	{
// 		// Norm of a sphere is the vector from the center to the point
// 		tmp = vec_add(&collision->obj->l->pos, &collision->parent_obj->pos);
// 		norm = vec_sub(&collision->point, tmp);
// 		vec_normalize(norm);
// 		our_free(tmp);
// 		return (norm);
// 	}
// 	else if (type == CYLINDER)
// 	{
// 		// Norm of a cylinder is the vector from the center to the point
// 		// Without takine the height into account
// 		tmp = vec_add(&collision->parent_obj->pos, &collision->obj->l->pos);
// 		norm = vec_sub(&collision->point, tmp);
// 		norm->z -= collision->dist * (collision->ray->dir->z);
// 		vec_normalize(norm);
// 		our_free(tmp);
// 		return (norm);
// 	}
// 	else
// 	{
// 		// To remove for release, just to debug
// 		printf("Error: light_get_norm: Unknown type\n");
// 		return (vec_new(0, 0, 0));
// 	}
// }

typedef void	(*t_collider_norm)(t_collision *, t_ray *);

void	collision_norm_switch(t_collision *col, t_e_prim type)
{
	static const t_collider_norm	map[] = {collider_sphere_norm, \
	collider_plane_norm, collider_cylinder_norm, NULL};
	map[type](col, col->ray);
}
