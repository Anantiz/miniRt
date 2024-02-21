#include "scene.h"
#include "miniRt.h"

/*

	Entry poit for the object creation and the collision query

*/


t_colision	*scene_collision_query(t_glob *glob, t_ray *ray)
{
	t_ll_obj	*obj;
	t_colision	*colision;

	obj = glob->scene->objects;
	colision = NULL;
	while (obj)
	{
		colision = obj->o->get_colision(obj->o->origin, obj->o->shape, ray);
		if (colision && not_too_far(ray, colision->point))
			return (colision);
		obj = obj->next;
	}
	return (NULL);
}





