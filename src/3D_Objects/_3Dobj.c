/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _3Dobj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 02:01:03 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 04:09:02 by aurban           ###   ########.fr       */
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
	(like new_sphere(), new_plane(), new_fighter_jet() etc...).

Thirdly:
	Each constructor will creates a t_csg tree, and returns a pointer to it.

*/

#include "_3Dshapes.h"

typedef t_csg	*(*t_constructor)(char **params);

/*
	Pretty warper, maybe it could do more lmfaoooo....
*/
static t_csg	*new_csg_tree(t_e_stype stypes, char **params)
{
	static const t_constructor	constructors[] = {new_sphere, new_plane, \
	new_cylinder, new_fighter_jet, new_penguin};

	return (constructors[stypes](params));
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
	static const char		*types[] = {"sp", "pl", "cy", "csg_fj", "csg_ping", NULL};
	static const t_e_stype	stypes[] = {SPHERE, PLANE, CYLINDER, FIGHTER_JET, PENGUIN};
	t_object				*obj;
	int						i;

	i = 0;
	while (types[++i])
	{
		if (!ft_strcmp(types[i], params[0]))
		{
			obj = our_malloc(sizeof(t_object));
			obj->type = stypes[i];
			parse_position(&obj->pos, params[1]);
			if (stypes[i] == SPHERE)
			{
				obj->ort = (t_vector){0, 0, 0};
				obj->csg = new_csg_tree(stypes, params + 2);
				return (obj);
			}
			parse_orientation(&obj->ort, params[2]);
			obj->csg = new_csg_tree(stypes, params + 3);
			return (obj);
		}
	}
	return (error_exit("Invalid object type, aborting."), NULL);
}
