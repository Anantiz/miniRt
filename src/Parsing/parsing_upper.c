/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_upper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:28:30 by aurban            #+#    #+#             */
/*   Updated: 2024/03/24 23:26:42 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	parse_camera_vectors(t_camera *cam);

// TO Improve
bool	parse_camera(t_glob *glob, char **line_tokens)
{
	static bool	cam_set = false;
	t_camera	*camera;

	if (cam_set)
		return (parse_error_msg(ERROR_DUPLICATE_CAM, NULL), FAILURE);
	cam_set = true;
	if (ft_tablen(line_tokens) != 4)
		return (parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL), FAILURE);
	camera = our_malloc(sizeof(t_camera));
	camera->pos = our_malloc(sizeof(t_vector));
	camera->dir = our_malloc(sizeof(t_vector));
	if (!parse_position(camera->pos, line_tokens[1]))
		return (parse_error_msg(ERROR_PARSE_POS, NULL), FAILURE);
	if (!parse_int(line_tokens[3], &camera->fov) || camera->fov <= 0 || camera->fov > 180)
		return (parse_error_msg(ERROR_PARSE_FOV, NULL), FAILURE);

	if (!parse_orientation(camera->dir, line_tokens[2]))
		return (parse_error_msg(ERROR_PARSE_ROT, NULL), FAILURE);
	vec_normalize(camera->dir);
	if (vec_cmp(camera->dir, &(t_vector){0, 0, 0}))
		return (parse_error_msg(ERROR_PARSE_ROT, NULL), FAILURE);
	parse_camera_vectors(camera);


	//Debug
	printf("Camera:\n");
	printf("\tPos:        ");
	print_vector(camera->pos);
	printf("\tDir:        ");
	print_vector(camera->dir);
	printf("\tRight_normal: ");
	print_vector(camera->right);
	printf("\tUp_normal:    ");
	print_vector(camera->up);
	printf("\n");
	glob->camera = camera;
	return (SUCCESS);
}

/*
Ambiant light rules:

- Can only be set once
- Must be a float between 0 and 1
- Must be followed by 3 int between 0 and 255 (r,g,b)
*/
bool	parse_ambiant(t_glob *g, char **line_tokens)
{
	static bool	ambiant_set = false;

	if (ambiant_set)
		return (parse_error_msg(ERROR_DUPLICATE_AMBIANT, NULL), FAILURE);
	if (ft_tablen(line_tokens) != 3)
		return (parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL), FAILURE);
	ambiant_set = true;
	if (!ft_is_float_format(line_tokens[1]))
		return (parse_error_msg(ERROR_PARSE_LINTESITY, NULL), FAILURE);
	g->scene->amb_intensity = ft_atoldb(line_tokens[1]);
	if (g->scene->amb_intensity > 1 || g->scene->amb_intensity < 0)
		return (parse_error_msg(ERROR_PARSE_LINTESITY, NULL), FAILURE);
	if (!parse_rgb(&g->scene->ambiant_rgb, line_tokens[2]))
		return (FAILURE);
	return (SUCCESS);
}

/*
	pos, birghtness, color(bonus)
*/
bool	parse_light(t_glob *glob, char **line_tokens)
{
	t_spot_light	*light;

	if (ft_tablen(line_tokens) != 4)
		return (parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL), FAILURE);
	light = our_malloc(sizeof(t_spot_light));
	if (!parse_position(&light->pos, line_tokens[1]))
		return (parse_error_msg(ERROR_PARSE_POS, NULL), FAILURE);
	if (!parse_double(line_tokens[2], &light->intensity_ratio) || light->intensity_ratio < 0 || light->intensity_ratio > 1)
		return (parse_error_msg(ERROR_PARSE_LINTESITY, NULL), FAILURE);
	if (!parse_rgb(&light->rgb, line_tokens[3]))
		return (parse_error_msg(ERROR_PARSE_RGB, NULL), FAILURE);
	scene_add_light(glob->scene, light);
	light->lumen = DEFAULT_LUMEN;
	return (SUCCESS);
}
