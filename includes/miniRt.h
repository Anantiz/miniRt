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

#define ERROR_PARSE_RGB			1
#define ERROR_PARSE_POS 		2
#define ERROR_PARSE_ROT			3
#define ERROR_PARSE_TOO_MANY	4
#define ERROR_DUPLICATE_AMBIANT	5
#define ERROR_DUPLICATE_CAM		6
#define ERROR_PARSE_FOV			7
#define ERROR_PARSE_LINTESITY	8

/*
	La direction devra etre calculer depuis rotatio et pos
*/
typedef	struct	s_camera
{
	t_vector	pos;
	t_vector	rotation;
	t_vector	direction; // Kinda the same thins as rotation ...
	t_vector	right;
	t_vector	up;
	int			fov;
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

// Pls don't ask why
typedef struct s_scene t_scene;
/*
	Ambient light is a fraud to simulate the sun light :(
		constrained between 0 and 1
*/
typedef struct s_glob
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pair_size		win_size;

	t_camera		*camera;
	t_scene			*scene;
}t_glob;


/* Parsing : Public*/

int					parse_map(t_glob *glob, char *path);

/* Parsing : Private*/

void				parse_error_msg(int error);
void				parse_rgb(t_rgb *color, char *str_color);
void				parse_position(t_vector *vector, char *str_pos);
void				parse_rotation(t_vector *vector, char *str_rot);

void				parse_ambiant(t_glob *glob, char **line_tokens);
void				parse_camera(t_glob *glob, char **line_tokens);
void				parse_light(t_glob *glob, char **line_tokens);

void				parse_cylinder(t_glob *glob, char **line_tokens);
void				parse_sphere(t_glob *glob, char **line_tokens);
void				parse_plane(t_glob *glob, char **line_tokens);

/* Captain Hook : Public */

void				cptn_hook_key(mlx_key_data_t keydata, void *glob_);

/* Rendering : Public*/

void				rtt_render(void *glob_);


#endif
