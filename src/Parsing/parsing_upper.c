/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_upper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:28:30 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 10:25:45 by aurban           ###   ########.fr       */
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
		parse_error_msg(ERROR_DUPLICATE_AMBIANT, NULL);
	if (ft_tablen(line_tokens) != 3)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL);
	ambiant_set = true;
	if (!ft_is_float_format(line_tokens[1]))
		parse_error_msg(ERROR_PARSE_LINTESITY, NULL);
	g->scene->amb_intensity = ft_atoldb(line_tokens[1]);
	if (g->scene->amb_intensity > 1 || g->scene->amb_intensity < 0)
		parse_error_msg(ERROR_PARSE_LINTESITY, NULL);
	parse_rgb(&g->scene->ambiant_rgb, line_tokens[2]);
}

void	parse_camera(t_glob *glob, char **line_tokens)
{
	static bool	cam_set = false;
	t_camera	*camera;

	if (cam_set)
		parse_error_msg(ERROR_DUPLICATE_CAM, NULL);
	cam_set = true;
	if (ft_tablen(line_tokens) != 4)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL);
	camera = our_malloc(sizeof(t_camera));
	camera->pos = our_malloc(sizeof(t_vector));
	camera->dir = our_malloc(sizeof(t_vector));
	parse_position(camera->pos, line_tokens[1]);
	parse_orientation(camera->dir, line_tokens[2]);
	if (camera->dir->x == 0 && camera->dir->y == 0 \
	&& camera->dir->z == 0)
		parse_error_msg(ERROR_PARSE_ROT, NULL);
	vec_normalize(camera->dir);
	camera->fov = parse_int(line_tokens[3]);
	if (camera->fov <= 0 || camera->fov > 180)
		parse_error_msg(ERROR_PARSE_FOV, NULL);

	// Now we want to get the right and up vector for ray-sampling

	camera->right = vec_get_ortho(camera->dir);
	vec_normalize(camera->right);
	// This Should logically, give an orthogonal vector to the two other
	camera->up = vec_cross_product(camera->right , camera->dir);
	vec_normalize(camera->up);

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
}

/*
	pos, birghtness, color(bonus)
*/
void	parse_light(t_glob *glob, char **line_tokens)
{
	t_spot_light	*light;

	if (ft_tablen(line_tokens) != LIGHT_PARAM_COUNT)
		parse_error_msg(ERROR_PARSE_WRONG_COUNT, NULL);
	light = our_malloc(sizeof(t_spot_light));
	parse_position(&light->pos, line_tokens[1]);
	if (!ft_is_float_format(line_tokens[2]))
		parse_error_msg(ERROR_PARSE_LINTESITY, NULL);
	light->intensity_ratio = ft_atoldb(line_tokens[2]);
	if (light->intensity_ratio < 0 || light->intensity_ratio > 1)
		parse_error_msg(ERROR_PARSE_LINTESITY, NULL);
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
	{
		printf("Invalid integer: %s\n", str);
		parse_error_msg(ERROR_PARSE_INT, NULL);
	}
	ret = ft_atoll_safe(str, INT_MAX, &valid);
	if (!valid)
		parse_error_msg(ERROR_PARSE_INT, NULL);
	return (ret);
}
