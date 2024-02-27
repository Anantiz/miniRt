/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:04:26 by aurban            #+#    #+#             */
/*   Updated: 2024/02/27 17:28:04 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

static t_lcol	*get_light_collision(t_spot_light *light, t_csg *obj, \
t_vector *point, t_vector *ray_dir)
{
	t_collision	*collision;
	t_lcol		*lcol;
	t_ray		ray;
	t_vector	*orthogonal;

	ray.origin = point;
	ray.direction = vector_sub(&light->pos, point);
	vector_normalizer(ray.direction);
	collision = query_collision(scene_getter(NULL), &ray);
	our_free(ray.direction);
	if (!collision)
		return (NULL);
	if (collision->obj != obj)
		return (our_free(collision), NULL);
	lcol = our_malloc(sizeof(t_lcol));
	lcol->light = light;
	lcol->dist = collision->dist;
	orthogonal = produit_vectoriel(ray_dir, ray_dir);
	lcol->theta = vec_get_angle_rad(orthogonal, ray.direction);
	our_free(orthogonal);
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
	int			i;

	light = scene_getter(NULL)->lights;
	root = NULL;
	i = -1;
	while (light)
	{
		collision = get_light_collision(light->l, obj, point, ray_dir);
		if (collision)
			add_light_collision(&root, collision);
		light = light->next;
	}
	return (root);
}
