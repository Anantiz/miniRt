#include "../../includes/miniRt.h"

extern FILE *debug_log_f;

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	// ray_tracing(glob);
	// sleep(5);
	(void)glob;
}

void	rtt_render_pixel(t_glob *glob, t_collision *collision, int x, int y, t_ray *ray)
{
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
		mlx_put_pixel(glob->img, x, y, PINK);
	else
	{
		t_lcol *light_col;
		light_col = query_visible_light(collision->obj, &collision->point, ray->direction);
		vector_normalizer(&(collision->point));
		mlx_put_pixel(glob->img, x, y, vector_to_color(&collision->point, light_adjust(light_col)));
		fprintf(debug_log_f, "\t~Collision\n");
	}
}

float	light_adjust(t_lcol *light_col)
{
	float		cos_angle;

	if (light_col)
		cos_angle = cos(light_col->theta);
	else
		cos_angle = 1;
	return (cos_angle);
}