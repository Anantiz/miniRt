#ifndef LIGHT_H
# define LIGHT_H

/*
	Module goal:

		Given a point, the light module will return a t_light_collision struct
		Which holds a list of all the lights that are visible from the point
*/

# include "libft.h"
# include "color_texture.h"
# include "vector.h"
# include "ray.h"
# include "scene.h"

typedef struct s_spot_light
{
	t_vector		pos;
	t_rgb			rgb;
	float			intensity_ratio;
	float			lumen;
}t_spot_light;
typedef t_spot_light t_slight;

// Alpha is given in radian
typedef struct s_light_collision
{
	t_spot_light				*light;
	float						dist;
	float						theta;

	struct s_light_collision	*next;
}t_light_collision;
typedef t_light_collision t_lcol;

#endif