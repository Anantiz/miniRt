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

/* RAY */

void		new_ray(t_camera *camera, int x, int y, t_ray *ray);
t_screen	*field_of_view(float fov);
t_vector	*ray_dir(t_camera *camera, t_screen *screen, float u, float v);
t_vector	*hit_point_to_color(t_collision *collision, t_ray *ray);

/* RAY BOUNCE */

t_vector	*ray_flect(t_ray *ray, t_vector *normal);
bool		ray_fract(t_vector *normal, t_vector *ray, float indice_refract, t_vector **refract);
t_rgb		color_combination(t_rgb *rgb, t_rgb *colorReflechie, t_rgb *colorRefractee, float refract, float reflect);
void		colorLocal(t_collision *collision, t_ray *ray);
t_rgb		trace_ray(t_ray *ray, t_scene *scene, int depth);
t_rgb		vec_rgb(int32_t x, int32_t y, int32_t z);
t_rgb		traceray_ret_condition(int	depth);
void		traceray_init(t_ray **ray_fraction, t_ray **ray_flection, t_rgb *colorReflect, t_rgb *colorRefract);

#endif