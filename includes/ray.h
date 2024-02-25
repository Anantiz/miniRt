#ifndef RAY_H
# define RAY_H

# include "miniRt.h"

/*
	Returned by a collision query
	Contains the object and the point of collision for the given ray

	Obj is the one there is a collision with
	Parent_obj is the group that contains the obj (if any use)
*/
typedef struct s_collision
{
	float			dist;
	t_vector		point;
	t_csg			*obj;
	t_object		*parent_obj;
}t_colision;


typedef	struct s_ray
{
	int			lumen;
	t_rgb		ray_color;

	t_vector	*origin;
	t_vector	*direction;
}t_ray;

typedef struct s_screen
{
	float	height_factor;
	float	width_factor;

}t_screen;

t_ray		*new_ray(t_camera *camera, float x, float y);

#endif