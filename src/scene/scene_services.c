#include "scene.h"
#include "miniRt.h"

void	scene_add_object(t_scene *scene, t_object *object)
{
	t_ll_obj	*node;

	node = tll_new_node(object);
	tll_add_back(&scene->objects, node);
	scene->objects_count++;
}
