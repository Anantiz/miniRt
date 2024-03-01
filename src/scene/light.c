#include "light.h"

/*
Cast a collison ray starting from the light point towards the point of interest
If the returned collision is the same as the object, then the light is visible

We then create a t_light_collision struct and add it to the list
-Calculate the distance (just a copy of the collision distance)
-Calculate the angle between the light and the normal of the object initial
ray collision (reverse light path, since we start from the camera to the light)

*/
static t_lcol	*get_light_collision(t_spot_light *light, t_csg *obj, \
t_vector *point, t_vector *ray_dir)
{
	t_collision	*collision;
	t_lcol		*lcol;
	t_ray		ray;
	t_vector	*orthogonal;

	ray.origin = point;
	ray.direction = sub_vector(&light->pos, point);
	vector_normalizer(ray.direction);
	collision = query_collision(scene_getter(NULL), &ray);
	if (!collision)
		return (our_free(ray.direction), NULL);
	if (collision->obj != obj)
		return (our_free(collision), NULL);
	if (vec_cmp(&collision->point, point) == false)
		return (our_free(collision), NULL);
	lcol = our_malloc(sizeof(t_lcol));
	lcol->light = light;
	lcol->dist = collision->dist;
	orthogonal = produit_vectoriel(ray_dir, ray_dir);
	lcol->theta = vec_get_angle_rad(orthogonal, ray.direction);
	our_free(orthogonal);
	our_free(ray.direction);
	return (lcol);
}

static void	add_light_collision(t_lcol **root, t_lcol *collision)
{
	t_lcol	*tmp;

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

	light = scene_getter(NULL)->lights;
	root = NULL;
	while (light)
	{
		collision = get_light_collision(light->l, obj, point, ray_dir);
		if (collision)
			add_light_collision(&root, collision);
		light = light->next;
	}
	return (root);
}
