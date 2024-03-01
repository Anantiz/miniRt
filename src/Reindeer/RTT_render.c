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
	(void)ray;
	if (x >= WIN_SIZE_X || y >= WIN_SIZE_Y || x < 0 || y < 0)
		return ;
	if (!collision)
		mlx_put_pixel(glob->img, x, y, GREY);
	else
	{
		t_lcol *light_col;
		light_col = query_visible_light(collision->obj, &collision->point, ray->direction);
		vector_normalizer(&(collision->point));
		mlx_put_pixel(glob->img, x, y, vector_to_color(&collision->point, light_adjust(light_col, collision)));
		fprintf(debug_log_f, "\t~Collision\n");
	}
}

float	light_adjust(t_lcol *light_col, t_collision *col)
{
	float		cos_angle;
	t_vector	*obj_center = add_vector(&col->obj->l->pos, &col->parent_obj->pos);

	if (light_col)
	{
		t_vector	*norm;
		norm = sub_vector(&col->point, obj_center);
		cos_angle = vec_dot_product((&light_col->light->pos), norm);
		// cos_angle = cos(cos_angle);
		if (cos_angle < 0)
			cos_angle = 0;
		fprintf(debug_log_f, "ca c'est ma fusee encule de ta mere la pute %f\n", cos_angle);
	}
	else
		cos_angle = 1;
	return (cos_angle);
}