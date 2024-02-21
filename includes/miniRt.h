#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "errno.h"
# include "fcntl.h"
# include "pair.h"
# include "scene.h"
# include "libft.h"
# include "vector.h"
# include "../libs/MLX42/include/MLX42/MLX42_Int.h"

#define SUCCESS				0
#define FAILURE				1
#define GO_FUCK_YOURSELF	-1

typedef	struct	s_camera
{
	t_vector	*pos;
	t_vector	*direction;
	t_vector	*right;
	t_vector	*up;
	double		fov;
}t_camera;

/*
Lumen is the light intensity.
	It follows the formula:
		lumen_colision = (1 / (distance * distance) * lumen_source) \
		* (1 - absorption_index)

The ray_color is dynamic and is updated at each collision.
	It follows the formula:
		ray_color = ray_color * (1 - absorption_index)
		+ object_color * absorption_index

TO BE updated at each collision !!!
*/
typedef	struct s_ray
{
	int			lumen;
	t_rgb		ray_color;
	t_vector	*origin;
	t_vector	*direction;
}t_ray;

/*
	Ambient light is a fraud to simulate the sun light :(
		constrained between 0 and 1
*/
typedef struct s_glob
{
	t_rgb			ambiant_rgb;
	float			ambient_light_intensity;
	t_camera		*camera;
	mlx_t			*mlx;
	mlx_image_t		*mlx_img;
	t_scene			*scene;
}t_glob;


/* Parsing : Public*/

int					parse_map(t_scene *scene, char *path);

/* Parsing : Private*/

int					parse_ambiant(t_scene *scene, char **tokens);
int					parse_camera(t_scene *scene, char **tokens);
int					parse_light(t_scene *scene, char **tokens);
int					parse_cylinder(t_scene *scene, char **tokens);
int					parse_sphere(t_scene *scene, char **tokens);
int					parse_plane(t_scene *scene, char **tokens);


#endif
