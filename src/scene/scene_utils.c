#include "scene.h"
#include "miniRt.h"

void	scene_add_object(t_glob *glob, t_object *object)
{
	t_ll_obj	*node;

	node = tll_new_node(object);
	tll_add_back(&glob->scene->objects, node);
	glob->scene->objects_count++;
}
