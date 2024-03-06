#include "light.h"
#define PRINT_SAMPLE 10000
int has_printed = -1;

static t_vector	*light_get_norm(t_collision *collision, t_e_prim type)
{
	t_vector	*norm;
	t_vector	*tmp;

	if (type == PLANE)
	{
		return (collision->obj->l->shape.plane.norm);
	}
	else if (type == SPHERE)
	{
		tmp = add_vector(&collision->parent_obj->pos, &collision->obj->l->pos);
		norm = sub_vector(&collision->parent_obj->pos, &collision->point);
		our_free(tmp);
		vector_normalizer(norm);
		return (norm);
	}
	else
		return (new_vector(0, 0, 0));
}

static void	light_free_norm(t_e_prim type, t_vector *norm)
{
	if (type == SPHERE)
		our_free(norm);
}

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
	t_collision	*obj_collision;
	t_lcol		*light_collision;
	t_ray		ray;
	t_vector	*norm;

	has_printed++;
	ray.pos = &light->pos;
	ray.dir = sub_vector(point, &light->pos);
	vector_normalizer(ray.dir);

// DIRECT LIGHT TEST
	obj_collision = query_collision(scene_getter(NULL), &ray);
	// if (csg->l->type == PLANE && has_printed % PRINT_SAMPLE == 0)
	// 	print_collision(obj_collision);
	if (!obj_collision)
		return (our_free(ray.dir), NULL);
	if (obj_collision->obj != csg) // Shadows, we put in gray for now, check for transparency later
		return (our_free(obj_collision), NULL);

// Basic data
	light_collision = our_malloc(sizeof(t_lcol));
	light_collision->light = light;
	light_collision->dist = obj_collision->dist;
	norm = light_get_norm(obj_collision, csg->l->type);

// Cos Angle between the light and the normal of the object
	light_collision->cos_angle = vec_dot_product(ray.dir, norm);
	// if (csg->l->type == PLANE && has_printed % PRINT_SAMPLE == 0)
	// {
	// 	printf("Norm:      ");
	// 	print_vector(norm);
	// 	printf("Ray dir:   ");
	// 	print_vector(ray.dir);
	// 	printf("cos_angle: %f\n", light_collision->cos_angle);
	// 	printf("\n");
	// }
	if (light_collision->cos_angle < 0) // The light is behind the object
	{
		// Later we will check for transparency

		// Should not be Handled like this
		// But because of the sign of the normal being random, sometimes the result will be inversed
		// TO DO: Makes it so that the sign of the normal don't matter
		if (csg->l->type == PLANE)
			light_collision->cos_angle = -light_collision->cos_angle;
	}
	our_free(obj_collision);
	light_free_norm(csg->l->type, norm);
	return (our_free(ray.dir), light_collision);
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
	light = scene_getter(NULL)->lights;
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
