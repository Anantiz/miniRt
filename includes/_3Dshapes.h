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
# include "vector.h"
# include "ray.h"
# include "color_texture.h"
# include "pair.h"
# include <math.h>

// Shapes
typedef enum e_stype
{
	SPHERE,
	PLANE,
	CYLINDER,
	FIGHTER_JET,
	PENGUIN

}t_e_stype;

// Operations
typedef enum e_otype
{
	UNION,
	INTERSECTION,
	DIFFERENCE,
}t_e_otype;

// CSG node type
typedef enum e_ntype
{
	LEAVE,
	OP,
}t_e_ntype;

typedef union u_shape // Specific geometric parameters
{
	struct s_sphere
	{
		float	rad;
	}sphere;

	struct s_plane
	{
		float	width;
		float	height;
	}plane;

	struct s_cylinder
	{
		float	rad;
		float	height;
	}cylinder;
}t_u_shape;

/*
The CSG tree

	The position and orientation are relative to the whole object not
	to the scnene.
To come:
	- Texture and Bump mapping
	- Material properties
	- Having the object component being independant light sources
*/
typedef struct s_csg_leave
{
	t_e_stype	type;

	t_vector	pos;
	t_vector	ort;

	t_u_shape	shape;

	t_rgb		color;
	// more to come

}t_csg_leave;

typedef struct s_csg_op
{
	t_e_otype		type;

	struct s_csg	*left;
	struct s_csg	*right;
}t_csg_op;

// l stands for leave
typedef union u_nd
{
	t_csg_leave	*l;
	t_csg_op	*op;
}t_u_nd;

typedef struct s_csg
{
	t_e_ntype	type;
	t_u_nd		nd;
}t_csg;

/*
Objects:
	A linked list of objects
		- position
		- orientation
		- CSG tree
		- next
ort=orientation
*/
typedef struct s_object
{
	t_vector			pos;
	t_vector			ort;

	t_csg				*csg;

	// So, the assignment only asks for primitives, so even tho I handle
	// the CSG tree, most of the time, the leaves will be the only thing
	// used.
	// This is why the parsing will mostly just parse primitives, that's why
	// I use the e_stype here, even tho a fighter jet is not a primitive.
	// ¯\_(ツ)_/¯
	t_e_stype			type;
	struct s_object		*next;
}t_object;


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

// Operations

t_csg				*new_csg_op(t_e_otype type, t_csg *left, t_csg *right);

// Leaves


// Because of the shitty norm we have to follow, I can't have more than
//5 parameters
// in a function, so I'll have to use a second function to add
//the texture and bump etc...
t_csg				*new_csg_leave(t_e_stype type, t_vector *pos, t_vector *ori, t_rgb color);
void				csg_leave_add(t_csg *csg, char **params); // to come

t_csg				*new_sphere(char **params);
t_csg				*new_plane(char **params); // Special case ... idk how to handle it cleanly
t_csg				*new_cylinder(char **params);
t_csg				*new_fighter_jet(char **params);
t_csg				*new_penguin(char **params);

/* Coliders : Public */

t_colision			*new_collision(t_object *obj, t_csg *csg, t_ray *ray, float t);

t_colision			*colider_sphere(t_object *obj, t_csg *csg, t_ray *ray);


#endif