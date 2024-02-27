#include "miniRt.h"

/*
Formula:
	E_point = (1 / distance^2) * E_origin

.Physics®

Return:
	The new lumen intensity at the colision point
*/
float	update_lumen_distance(float distance, float lumen)
{
	return (lumen = (1 / (distance * distance)));
}
