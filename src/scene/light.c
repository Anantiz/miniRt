#include "light.h"

/*
Cast a collison ray starting from the light point towards the point of interest
If the returned collision is the same as the object, then the light is visible

We then create a t_light_collision struct and add it to the list
-Calculate the distance (just a copy of the collision distance)
-Calculate the angle between the light and the normal of the object initial
ray collision (reverse light path, since we start from the camera to the light)

*/
static t_lcol	*get_light_collision(t_spot_light *light, t_csg *csg, \
t_vector *point)
{
	t_collision	*obj_col;
	t_lcol		*light_col;
	t_ray		ray;

	ray.pos = &light->pos;
	ray.dir = vec_sub(point, &light->pos);
	vec_normalize(ray.dir);

	// Direct light collision with the object, later, it will check for more...
	obj_col = query_collision(fetch_scene(NULL), &ray);
	if (!obj_col)
		return (our_free(ray.dir), NULL);
	if (obj_col->obj != csg) // Shadows, we put in gray for now, check for transparency later
		return (our_free(obj_col), NULL);


	light_col = our_malloc(sizeof(t_lcol));
	light_col->light = light; // For color and intensity
	light_col->dist = obj_col->dist; // For light dispersion
	light_col->cos_angle = -vec_dot_product(ray.dir, obj_col->norm); // For light incidency
	if (light_col->cos_angle < 0) // The light is behind the object
	{
		// Later we will check for transparency
		light_col->cos_angle = 0;//-light_col->cos_angle; // That's cheating, but fck it
	}
	/*
		Add some cheat function, to put the cos_angle to zero if a
		plane is in between the light and the camera.
		(because right now, the plane is always visible from the camera even
		if the light is behind it, which is not true in real life.)
	*/
	del_collision(obj_col);
	return (our_free(ray.dir), light_col);
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

t_lcol	*query_visible_light(t_csg *obj , t_vector *point, t_vector *ray_dir)
{
	t_ll_obj	*light;
	t_lcol		*collision;
	t_lcol		*root;

	(void)ray_dir; // Variable to be removed I guess
	light = fetch_scene(NULL)->lights;
	root = NULL;
	while (light)
	{
		collision = get_light_collision(light->l, obj, point);
		if (collision)
			add_light_collision(&root, collision);
		light = light->next;
	}
	return (root);
}
