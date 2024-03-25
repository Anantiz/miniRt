/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:43:19 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 22:08:39 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_3Dshapes.h"

/*
If you ever add new shapes, pay attention to the order of the enum
as the collider_switch function uses it to call the right collider

MEMO:
t_e_prim
		Order:
			SPHERE,
			PLANE,
			CYLINDER,
		// To come
			CONE,
			PRSIM
			CUBOID,
			PARABOLOID,
*/

// For cleaner code
typedef t_collision	*(*t_collider)(t_object *,t_leaf *, t_ray *);

/*
	Pretty warper to get the right collider
*/
t_collision	*collider_switch(t_object *obj, t_ray *ray, t_csg *csg)
{
	static const t_collider	map[] = {collider_sphere, collider_plane, \
	collider_cylinder, NULL};
	return (map[csg->l->type](obj, csg->l, ray));
}

/*
               ___               ___                 ___                   ___
              / 0_)             / 0_)               / 0_)                 / 0_)
     _.----._/ /       _.----._/ /         _.----._/ /           _.----._/ /
    /         /       /         /         /         /           /         /
 __/ (  | (  |     __/ (  | (  |       __/ (  | (  |         __/ (  | (  |
/__.-'|_|--|_|    /__.-'|_|--|_|      /__.-'|_|--|_|        /__.-'|_|--|_|

*/
t_collision	*collider_union(t_collision **collision)
{
	if (collision[0])
	{
		// Returns the closest collision out of the two
		if (collision[1] && collision[0]->t < collision[1]->t)
			return (del_collision(collision[1]), collision[0]);
		// Either returns the closer collision or NULL
		return (del_collision(collision[0]), collision[1]);
	}
	return (NULL);
}

/*

                         .       .
                        / `.   .' \
                .---.  <    > <    >  .---.
                |    \  \ - ~ ~ - /  /    |
                 ~-..-~             ~-..-~
             \~~~\.'                    `./~~~/
   .-~~^-.    \__/                        \__/
 .'  O    \     /               /       \  \
(_____,    `._.'               |         }  \/~~~/
 `----.          /       }     |        /    \__/
       `-.      |       /      |       /      `. ,~~|
           ~-.__|      /_ - ~ ^|      /- _      `..-'   f: f:
                |     /        |     /     ~-.     `-. _||_||_
                |_____|        |_____|         ~ - . _ _ _ _ _>

*/
t_collision	*collider_inter(t_collision **collision)
{
	if (collision[0] && collision[1])
	{
		// If both collisions are valid, return the closest one
		if (collision[0]->t < collision[1]->t)
			return (del_collision(collision[1]), collision[0]);
		return (del_collision(collision[0]), collision[1]);
	}
	del_collision(collision[0]);
	del_collision(collision[1]);
	return (NULL);
}

/*
	Returns the left node collisions IF:
		- The left node is valid
		- The right node is NULL
*/
t_collision	*collider_diff(t_collision **collision)
{
	if (collision[0] && !collision[1])
		return (collision[0]);
	del_collision(collision[0]);
	del_collision(collision[1]);
	return (NULL);
}
