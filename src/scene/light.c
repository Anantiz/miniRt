#include "light.h"

// For faster access to the scene, pass it as a paramater later
extern t_scene *g_scene;
bool	print_allow = false;
/*
Cast a collison ray starting from the light point towards the point of interest
If the returned collision is the same as the object, then the light is visible

We then create a t_light_collision struct and add it to the list
-Calculate the distance (just a copy of the collision distance)
-Calculate the angle between the light and the normal of the object initial
ray collision (reverse light path, since we start from the camera to the light)

*/
static t_lcol	*get_light_collision(t_spot_light *light, t_leave *csg, \
t_vector *point)
{
	t_collision	*obj_col;
	t_lcol		*light_col;
	t_ray		light_ray;

	light_ray.pos = &light->pos;
	light_ray.dir = vec_sub(point, &light->pos);
	vec_normalize(light_ray.dir);
	// Direct light collision with the object, later, it will check for more...
	obj_col = query_collision(g_scene, &light_ray);
	if (!obj_col)
		return (our_free(light_ray.dir), NULL);
	if (obj_col->csg != csg) // Shadows, we put in gray for now, check for transparency later
		return (free2(obj_col, light_ray.dir), NULL);

	light_col = our_malloc(sizeof(t_lcol));
	light_col->light = light; // For color and intensity
	light_col->dist = obj_col->dist; // For light dispersion
	light_col->cos_angle = -vec_dot_product(light_ray.dir, obj_col->norm); // For light incidency

	if (light_col->cos_angle < 0) // The light is behind the object
	{
		light_col->cos_angle = 0;//light_col->cos_angle; // Cuz sometimes the normal is inverted
	}

	if (csg->type == CYLINDER) // Cuz normal is not yet implemented
	{
		light_col->cos_angle = 1;
	}
	/*
		Add some cheat function, to put the cos_angle to zero if a
		plane is in between the light and the camera.
		(because right now, the plane is always visible from the camera even
		if the light is behind it, which is not true in real life.)
	*/
	del_collision(obj_col);
	return (our_free(light_ray.dir), light_col);
}

static void	add_light_collision(t_lcol **root, t_lcol *collision)
{
	t_lcol	*tmp;

	collision->next = NULL;
	if (!*root)
	{
		*root = collision;
		return ;
	}
	tmp = *root;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = collision;
}

t_lcol	*query_visible_light(t_collision *coll)
{
	t_ll_obj	*light;
	t_lcol		*light_collision;
	t_lcol		*root;

	light = fetch_scene(NULL)->lights;
	root = NULL;
	while (light)
	{
		light_collision = get_light_collision(light->l, coll->csg, &coll->point);
		if (light_collision)
			add_light_collision(&root, light_collision);
		light = light->next;
	}
	return (root);
}
