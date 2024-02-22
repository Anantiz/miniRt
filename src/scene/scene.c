#include "scene.h"

t_scene	*scene_new(void)
{
	t_scene	*scene;

	scene = our_malloc(sizeof(t_scene));
	scene->objects = NULL;
	scene->objects_count = 0;
	return (scene);
}

/*
Note:
	This function does update the `lumen' field of the ray
	based on the distance between the ray's origin and the colision point
	and returns a NULL colision if the lumen is 0 (too far)...
Return:
	No collision found
		-> NULL
	Collision found
		-> t_colision
*/
t_colision	*scene_collision_query(t_scene *scene, t_ray *ray)
{
	t_ll_obj	*obj;
	t_colision	*colision;

	obj = scene->objects;
	colision = NULL;
	while (obj)
	{
		colision = obj->o->get_colision(obj->o->origin, obj->o->shape, ray);
		if (colision)
		{
			ray->lumen = update_lumen_distance(ray, colision->point);
			if (ray->lumen == 0)
				return (our_free(colision), NULL);
			return (colision);
		}
		obj = obj->next;
	}
	return (NULL);
}
