/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_upper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:28:30 by aurban            #+#    #+#             */
/*   Updated: 2024/02/28 15:07:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

#ifdef BONUS
#define LIGHT_PARAM_COUNT 4
#else
#define LIGHT_PARAM_COUNT 4
#endif

#define M_PI 3.14159265358979323846

/*
Ambiant light rules:

- Can only be set once
- Must be a float between 0 and 1
- Must be followed by 3 int between 0 and 255 (r,g,b)
*/
void	parse_ambiant(t_glob *g, char **line_tokens)
{
	static bool	ambiant_set = false;

	if (ambiant_set)
		parse_error_msg(ERROR_DUPLICATE_AMBIANT);
	if (ft_tablen(line_tokens) != 3)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT);
	ambiant_set = true;
	if (!ft_is_float_format(line_tokens[1]))
		parse_error_msg(ERROR_PARSE_LINTESITY);
	g->scene->amb_intensity = ft_atoldb(line_tokens[1]);
	if (g->scene->amb_intensity > 1 || g->scene->amb_intensity < 0)
		parse_error_msg(ERROR_PARSE_LINTESITY);
	parse_rgb(&g->scene->ambiant_rgb, line_tokens[2]);
}

void	parse_camera(t_glob *glob, char **line_tokens)
{
	static bool	cam_set = false;
	t_camera	*camera;

	if (cam_set)
		parse_error_msg(ERROR_DUPLICATE_CAM);
	cam_set = true;
	if (ft_tablen(line_tokens) != 4)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT);
	camera = our_malloc(sizeof(t_camera));
	camera->pos = our_malloc(sizeof(t_vector));
	camera->direction = our_malloc(sizeof(t_vector));
	parse_position(camera->pos, line_tokens[1]);
	parse_orientation(camera->direction, line_tokens[2]);
	if (camera->direction->x == 0 && camera->direction->y == 0 \
	&& camera->direction->z == 0)
		parse_error_msg(ERROR_PARSE_ROT);
	vector_normalizer(camera->direction);
	camera->fov = parse_int(line_tokens[3]);
	if (camera->fov <= 0 || camera->fov > 180)
		parse_error_msg(ERROR_PARSE_FOV);
	camera->right = produit_vectoriel(&(t_vector){0, 1, 0}, camera->direction);
	vector_normalizer(camera->right);
	camera->up = produit_vectoriel(camera->right , camera->direction);
	vector_normalizer(camera->up);
	print_vector(camera->right);
	print_vector(camera->up);
	print_vector(camera->direction);
	glob->camera = camera;
}

/*
	pos, birghtness, color(bonus)
*/
void	parse_light(t_glob *glob, char **line_tokens)
{
	t_spot_light	*light;

	if (ft_tablen(line_tokens) != LIGHT_PARAM_COUNT)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT);
	light = our_malloc(sizeof(t_spot_light));
	parse_position(&light->pos, line_tokens[1]);
	if (!ft_is_float_format(line_tokens[2]))
		parse_error_msg(ERROR_PARSE_LINTESITY);
	light->intensity_ratio = ft_atoldb(line_tokens[2]);
	if (light->intensity_ratio < 0 || light->intensity_ratio > 1)
		parse_error_msg(ERROR_PARSE_LINTESITY);
	parse_rgb(&light->rgb, line_tokens[3]);
	scene_add_light(glob->scene, light);
	light->lumen = DEFAULT_LUMEN;
}

// Cuz I don't wanna do an other file just for this

int	parse_int(char *str)
{
	int	valid;
	int	ret;

	valid = 1;
	if (!ft_is_int_format(str))
		parse_error_msg(ERROR_PARSE_INT);
	ret = ft_atoll_safe(str, INT_MAX, &valid);
	if (!valid)
		parse_error_msg(ERROR_PARSE_INT);
	return (ret);
}
