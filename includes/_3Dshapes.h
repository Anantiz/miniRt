/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _3Dshapes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:29:27 by aurban            #+#    #+#             */
/*   Updated: 2024/02/23 14:29:40 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _3DSHAPES_H
# define _3DSHAPES_H

/*

The CSG tree (Constructive Solid Geometry)

	It is a binary tree that represents the object. The leaves are the basic
	primitives objects (sphere, plane, cylinder) and the nodes are operations
	(union, intersection, difference) between the left and right children.
		Union: Both objects are visible
		Intersection: Only the common part is visible
		Difference: Only the left object is visible
*/

# include "libft.h"
# include "forward_declaration.h"
# include "vector.h"
# include "ray.h"
# include "color_texture.h"
# include "parsing.h"
# include <math.h>

typedef struct s_ray t_ray;

// Shapes
typedef enum e_objtype
{
	P_SPHERE,
	P_PLANE,
	P_CYLINDER,
	P_FIGHTER_JET,
	P_PENGUIN

}t_e_objt;

// Shapes
typedef enum e_primitive
{
	SPHERE,
	PLANE,
	CYLINDER,
}t_e_prim;

// Operations
typedef enum e_ndtype
{
	LEAVE,
	UNION,
	INTER,
	DIFF,
}t_e_ndtype;

typedef union u_shape // Specific geometric parameters
{
	struct s_sphere
	{
		float	rad;
	}sphere;

	struct s_plane
	{
		t_vector	*norm; // Do not free
	}plane;

	struct s_cylinder
	{
		float	rad;
		float	height;
	}cylinder;
}t_u_shape;

/*
The CSG tree (Constructive Solid Geometry)

	The position and orientation are relative to the whole object not
	to the scnene.
To come:
	- Texture and Bump mapping
	- Material properties
	- Having the object component being independant light sources
*/
typedef struct s_csg_leave
{
	t_vector		pos;
	t_vector		dir;

	t_e_prim		type;
	t_u_shape		shape;

	t_rgb			rgb;
	// more to come
	// Materials properties
}t_leave;

typedef struct s_csg
{
	t_e_ndtype		type;

	t_leave			*l;
	struct s_csg	*left;
	struct s_csg	*right;
}t_csg;

/*
Objects:
	A linked list of objects
		- position
		- orientation
		- CSG tree
		- next
dir=orientation
*/
typedef struct s_object
{
	t_vector			pos;
	t_vector			dir;

	t_csg				*csg;

	t_e_objt			type;
	struct s_object		*next;
}t_object;

typedef struct s_collision
{
	float			dist;
	t_vector		point;
	t_csg			*obj;
	t_object		*parent_obj;
}t_collision;


/*******************************************************************************

███████╗██╗   ██╗███╗   ██╗ ██████╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
██╔════╝██║   ██║████╗  ██║██╔════╝╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
█████╗  ██║   ██║██╔██╗ ██║██║        ██║   ██║██║   ██║██╔██╗ ██║███████╗
██╔══╝  ██║   ██║██║╚██╗██║██║        ██║   ██║██║   ██║██║╚██╗██║╚════██║
██║     ╚██████╔╝██║ ╚████║╚██████╗   ██║   ██║╚██████╔╝██║ ╚████║███████║
╚═╝      ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝

*******************************************************************************/


/* CSG, broad constructors */

t_object			*new_object(char **params);
t_csg				*new_csg(char **params);

// Because of the shitty norm we have to follow, I can't have more than
//5 parameters
// in a function, so I'll have to use a second function to add
//the texture and bump etc...
t_csg				*new_csg_leave(t_e_prim type, t_vector *pos, \
t_vector *ori, t_rgb color);
void				csg_leave_add(t_csg *csg, char **params); // to come

// Primitive constructors : Private
// Return a single leaf

t_csg				*pr_new_sphere(char **params);
t_csg				*pr_new_plane(char *color); // Special case ... idk how to handle it cleanly, i guess just a Null shape
t_csg				*pr_new_cylinder(char **params);

// CSG constructors : Public
// Return the root of the CSG tree

t_csg				*obj_new_sphere(t_object *obj, char **params);
t_csg				*obj_new_plane(t_object *obj, char **params); // Special case ... idk how to handle it cleanly, i guess just a Null shape
t_csg				*obj_new_cylinder(t_object *obj, char **params);
t_csg				*obj_new_fighter_jet(t_object *obj, char **params);
t_csg				*obj_new_penguin(t_object *obj, char **params);

/* Coliders : Private */

t_collision			*collider_union(t_collision **collision);
t_collision			*collider_inter(t_collision **collision);
t_collision			*collider_switch(t_object *obj, t_ray *ray, t_csg *csg);
t_collision			*hadron_collider(t_object *obj, t_ray *ray, t_csg *csg);
t_collision			*new_collision(t_object *obj, t_csg *csg, t_ray *ray, float t);

t_collision			*collider_sphere(t_object *obj, t_csg *csg, t_ray *ray);
t_collision			*collider_plane(t_object *obj, t_csg *csg, t_ray *ray);
t_collision			*collider_cylinder(t_object *obj, t_csg *csg, t_ray *ray);

/* Trash :*/

void				del_collision(t_collision *collision);
void				print_collision(t_collision *collision);


#endif