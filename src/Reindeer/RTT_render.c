#include "../../includes/miniRt.h"

/* This one is a loop_hook, called every frame*/
void	rtt_render(void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	// ray_tracing(glob);
	// sleep(5);
	(void)glob;
}



void	rtt_render_pixel(t_rgb *rgb, t_glob *glob, int x, int y)
{
	FILE *file = fopen("rendering.log", "a"); // Ouvre le fichier en mode ajout
	fprintf(file, "r = %u | ", rgb->r);
	fprintf(file, "g = %u | ", rgb->g);
	fprintf(file, "b = %u\n", rgb->b);

	mlx_put_pixel(glob->img, x, y, vector_to_color(1, rgb));
	fclose(file);
}
