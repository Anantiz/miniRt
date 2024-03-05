#ifndef RAY_H
# define RAY_H

# include "forward_declaration.h"
# include "vector.h"
# include "color_texture.h"

/*
	Returned by a collision query
	Contains the object and the point of collision for the given ray

	Obj is the one there is a collision with
	Parent_obj is the group that contains the obj (if any use)
*/
typedef	struct s_ray
{
	int			lumen;
	t_rgb		ray_color;

	t_vector	*pos;
	t_vector	*dir;
}t_ray;

typedef struct s_screen
{
	float	height_factor;
	float	width_factor;

}t_screen;

t_ray		*new_ray(t_camera *camera, int x, int y);
t_screen	*field_of_view(float fov, float aspect_ratio);
t_vector	*ray_dir(t_camera *camera, t_screen *screen, float u, float v);
t_vector	*hit_point_to_color(t_collision *collision, t_ray *ray);

#endif