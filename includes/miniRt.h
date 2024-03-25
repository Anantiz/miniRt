#ifndef MINIRT_H
# define MINIRT_H

#define DEBUG
#define SAMPLE_RATE 20000

// Larger ones for final rendering
// #define WIN_SIZE_X	2880
// #define WIN_SIZE_Y	1620

// #define WIN_SIZE_X 2560
// #define WIN_SIZE_Y 1440

// # define WIN_SIZE_X	1920
// # define WIN_SIZE_Y	1080
// # define WIN_SIZE_X	960
// # define WIN_SIZE_Y	540
<<<<<<< HEAD

// Small for development
=======
>>>>>>> loris
// # define WIN_SIZE_X	640
// # define WIN_SIZE_Y	360
# define WIN_SIZE_X	320
# define WIN_SIZE_Y	180
<<<<<<< HEAD

// Micro window for real-time rendering (we don't have GPU)
// # define WIN_SIZE_X	160
// # define WIN_SIZE_Y	90
// # define WIN_SIZE_X	80
// # define WIN_SIZE_Y	45
=======
>>>>>>> loris

# define DEFAULT_LUMEN		1000
# define DEFAULT_INTENSITY	0.6

# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <float.h>

# include "libft.h"
# include "forward_declaration.h"

# include "vector.h"
# include "color_texture.h"
# include "ray.h"
# include "_3Dshapes.h"
# include "light.h"
# include "scene.h"

# include "parsing.h"
# include "../libs/MLX42/include/MLX42/MLX42_Int.h"

# define SUCCESS				0
# define FAILURE				1
# define GO_FUCK_YOURSELF		-1

extern const char *shape_names[]; // To remove for release
extern FILE *debug_log_f;

// Pls don't ask why
typedef struct s_scene t_scene;

typedef	struct	s_camera
{
	t_vector	*pos;
	t_vector	*dir;
	t_vector	*right;
	t_vector	*up;
	int			fov;
	double		rad_fov;
	double		screen_ratio;
}t_camera;

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

	bool			update; // The camera moved so compute a new frame
	int				tick;	// The current frame since program start
}t_glob;

void				ray_tracing(t_glob *glob);


/* Captain Hook : Public */

void				cptn_hook_key(mlx_key_data_t keydata, void *glob_);

/* Rendering : Public*/

void				rtt_render(void *glob_);
void				rtt_render_pixel(t_rgb *rgb, t_glob *glob, int x, int y);

/* DEBUG */

void				print_vector(t_vector *vector);
void				print_collision(t_collision *collision);
t_glob				*fetch_glob(t_glob *glob);

#endif