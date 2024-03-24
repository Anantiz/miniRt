/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _3Dobj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 02:01:03 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:21:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Constructor hierarchy:

Firstly:
	New_object(), parses it's geometric parameters relative to the scene.
	(parameters obtained from file parsing).
	Return a pointer to the object.

Secondly:
	The new_object() function will take care of calling the right constructor
	(like pr_new_sphere(), new_plane(), new_fighter_jet() etc...).

Thirdly:
	Each constructor will creates a t_csg tree, and returns a pointer to it.

*/

#include "_3Dshapes.h"

typedef t_csg	*(*t_constructor)(t_object *obj, char **params);

/*
	Pretty warper, maybe it could do more lmfaoooo....
*/
static t_csg	*new_csg_tree(t_object *obj, t_e_objt stypes, char **params)
{
	static const t_constructor	constructors[] = {obj_new_sphere, obj_new_plane, \
	obj_new_cylinder, obj_new_fighter_jet, obj_new_penguin};

	return (constructors[stypes](obj, params));
}

/*
Firstly:
	String + ptr to the constructor, if None is found, exit with an error.
Secondly:
	Basic parsing for the object's parameters
Thirdly:
	Will call the right constructor
*/
t_object	*new_object(char **params)
{
	static const char		*types[] = {"sp", "pl", "cy", "csg_fj", "csg_peng", NULL};
	static const t_e_objt	stypes[] = {OBJ_SPHERE, OBJ_PLANE, OBJ_CYLINDER,OBJ_FIGHTER_JET, OBJ_PENGUIN};
	t_object				*obj;
	int						i;

	i = -1;
	while (types[++i])
	{
		if (!ft_strcmp(types[i], params[0]))
		{
			obj = our_malloc(sizeof(*obj));
			obj->type = stypes[i];
			if (!parse_position(&obj->pos, (params++)[1]))
				return (NULL);
			if (stypes[i] == OBJ_SPHERE) // Sphere doesn't have a direction
				obj->dir = (t_vector){0, 0, 0};
			else
				if (!parse_orientation(&obj->dir, (params++)[1]))
					return (NULL);
			obj->csg = new_csg_tree(obj, stypes[i], params + 1);
			if (obj->csg)
				return (obj);
		}
	}
	return (NULL);
}
