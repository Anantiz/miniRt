#include "scene.h"

t_object	*new_object(t_vector *origin)
{
	t_object	*object;

	object = our_malloc(sizeof(t_object));

	return (object);
}
