#include "miniRt.h"

/*
Formula:
	E_point = (1 / distance^2) * E_origin

.Physics®

Return:
	The new lumen intensity at the colision point
*/
int	update_lumen_distance(t_ray *ray, t_vector *point)
{
	float	distance;
	float	lumen;

	distance = vector_distance(ray->origin, point);
	lumen = (1 / (distance * distance)) * ray->lumen;
	ray->lumen = lumen;
	return ((int)lumen);
}
