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

	3D SHAPES

	This section only focuses on the shapes themselves, not the objects.
	Thus we do not care about position or rotation.
	We only care about the shape properties.
		- Height, width, depth, radius, etc.
	List of shape to implement:
		- Sphere
		- Plane
		- Cylinder
		- Cube
		- Cone
		- Pyramid
		- Prism
		- Ellipsoid
		- Paraboloid
		- Torus
	We will provide:
		A union + enum to store the different shapes
		A structure for each shape
		A function to create a shape
		A function to get collision with a shape
			-This function will return a t_collision structure
			-They will be stored as a polymorphic function in
			 the t_object structure because of data separation
			 (The shape properties in here and the object positional
			 properties in the t_object structure)
*/

# include "vector.h"

typedef enum e_shape
{
	SPHERE,
	PLANE,
	CYLINDER,
	CUBE,
	CONE,
	PYRAMID,
	PRISM,
	ELLIPSOID,
	PARABOLOID,
}t_e_shape;

typedef struct s_sphere
{
	float		radius;
}t_sphere;

typedef struct s_plane
{
	t_vector	normal;
	float		distance;
}t_plane;

typedef struct s_cylinder
{
	float		radius;
	float		length;
}t_cylinder;

typedef struct s_cuboid
{
	float		width;
	float		length;
	float		height;
}t_cuboid;

typedef struct s_cone
{
	float		angle;
	float		height;
	float		radius;
}t_cone;

// Square with triangles closing it
typedef struct s_pyramid
{
	float		height;
	float		base_width;
	float		base_height;
}t_pyramid;

// Wide rectangle
typedef struct s_prism
{
	float		height;
	float		base_width;
	float		base_length;
}t_prism;

typedef struct s_ellipsoid
{
	float		radius_x;
	float		radius_y;
	float		radius_z;
}t_ellipsoid;

typedef struct s_paraboloid
{
	float		height;
	float		radius;
	float		angle;
}t_paraboloid;

typedef struct s_torus
{
	float		radius;
	float		tube_radius;
}t_torus;

typedef union u_shapes
{
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
	t_cuboid			*cuboid;
	t_cone				*cone;
	t_pyramid			*pyramid;
	t_prism				*prism;
	t_ellipsoid			*ellipsoid;
	t_paraboloid		*paraboloid;
	t_torus				*torus;
}t_u_shape;

/* Parse shapes : Public */

t_sphere			*parse_sphere(char **line_tokens);



#endif