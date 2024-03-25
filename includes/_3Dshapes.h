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
	primitives objects (sphere, plane, cylinder etc...) and the nodes are operations
	(union, intersection, difference) between the left and right children.
		Union: Both objects are visible
		Intersection: Only the common part is visible
		Difference: Only the left object is visible

Note about Directions/Orientation vectors:
	Curretly we define the orientation of an object as a normalized vector
	pointing is a direction.
	There is a triplet of Eulers angles associated with said vector.
	e.i. Vector(0,0,1) means we will rotate the object's default orientation
	such that it points in the direction of the vector.
	If the object defaults orientation is (1,0,0), then we will make a 90°
	rotation around the Y axis to make it point in the direction of the vector.
*/

# include "libft.h"
# include "forward_declaration.h"
# include "vector.h"
# include "ray.h"
# include "color_texture.h"
# include "parsing.h"
# include <math.h>

typedef struct s_ray t_ray;

// Objects
typedef enum e_objtype
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_FIGHTER_JET,
	OBJ_PENGUIN
}t_e_objt;

// Shapes
typedef enum e_primitive
{
	SPHERE,
	PLANE,
	CYLINDER,
	CUBOID,
}t_e_prim;

// Operations
typedef enum e_ndtype
{
	LEAF,
	UNION,
	INTER,
	DIFF,
}t_e_ndtype;

typedef union u_shape // Specific geometric parameters
{
	struct s_sphere
	{
		double	r;
		double	r2;
	}sphere;

	struct s_plane
	{
		t_vector	norm; // Do not free
	}plane;

	struct s_cylinder
	{
		double		r;
		double		r2;
		double		h;
		int			norm_side;
		t_vector	circle_norm; // The non-cap norm
	}cylinder;

	struct s_cuboid
	{
		double		h;
		double		w;
		double		d;
		t_vector	norm_h;
		t_vector	norm_w; // The norm of the width is the overall direction
		t_vector	norm_d;
	}cuboid;
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
typedef struct s_csg_leaf
{
	t_vector		pos;
	t_vector		dir;

	t_e_prim		type;
	t_u_shape		shape;

	t_rgb			rgb;
	double			reflect;
	double			refract;
}t_leaf;

typedef struct s_csg
{
	t_e_ndtype		type;

	t_leaf			*l;
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
	double			t;
	t_rgb			rgb;
	t_vector		point;
	t_leaf			*csg;
	t_object		*obj;
	t_ray			*ray;
	t_vector		norm;
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
t_csg				*csg_new_union(void);
t_csg				*csg_new_inter(void);
t_csg				*csg_new_diff(void);


// Primitive constructors : Private
// Return a single leaf

t_csg				*pr_new_sphere(t_vector coordinates[2], char **params);
t_csg				*pr_new_plane(char *color); // Special case ... idk how to handle it cleanly, i guess just a Null shape
t_csg				*pr_new_cylinder(t_vector coordinates[2], char **params);

// CSG constructors : Public
// Return the root of the CSG tree

t_csg				*obj_new_sphere(t_object *obj, char **params);
t_csg				*obj_new_plane(t_object *obj, char **params); // Special case ... idk how to handle it cleanly, i guess just a Null shape
t_csg				*obj_new_cylinder(t_object *obj, char **params);
t_csg				*obj_new_fighter_jet(t_object *obj, char **params);
t_csg				*obj_new_penguin(t_object *obj, char **params);

/* Coliders : Private */

// CSG tree solver

t_collision			*collider_union(t_collision **collision);
t_collision			*collider_inter(t_collision **collision);
t_collision			*collider_diff(t_collision **collision);
t_collision			*collider_switch(t_object *obj, t_ray *ray, t_csg *csg);
t_collision			*hadron_collider(t_object *obj, t_ray *ray, t_csg *csg);

// Collision constructor
void				collision_norm_switch(t_collision *col, t_e_prim type);
t_collision			*new_collision(t_object *obj, t_leaf *csg, t_ray *ray, \
double t);

// Individual colliders + Norms

t_collision			*collider_sphere(t_object *obj, t_leaf *csg, t_ray *ray);
void				collider_sphere_norm(t_collision *col, t_ray *ray);

t_collision			*collider_plane(t_object *obj, t_leaf *csg, t_ray *ray);
double	plane_intersection(t_vector *plane_pos, t_vector *plane_norm, t_vector \
*ray_pos, t_vector *ray_dir);


void				collider_plane_norm(t_collision *col, t_ray *ray);

t_collision			*collider_cylinder(t_object *obj, t_leaf *csg, t_ray *ray);
double				cy_circle_intersection(t_vector *ray_pos, \
t_vector *ray_dir, double r);
double				cy_cap_intersection(t_vector *ray_pos, t_vector *ray_dir, \
double r, double h);
void				collider_cylinder_norm(t_collision *col, t_ray *ray);

/* Trash */

void				del_collision(t_collision *collision);
void				print_collision(t_collision *collision);

#endif