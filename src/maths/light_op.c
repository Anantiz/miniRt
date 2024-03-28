#include "miniRt.h"

/*
Formula:
	E_point = (1 / distance^2) * E_origin

.Physics®

Return:
	The new lumen intensity at the colision point
*/
double	update_lumen_distance(double distance, double lumen)
{
	return (lumen *= (1 / (distance * distance)));
}
