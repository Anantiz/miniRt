/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:45:02 by aurban            #+#    #+#             */
/*   Updated: 2024/02/24 15:50:42 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	scene_parse_sphere(t_glob *glob, char **line_tokens)
{
	t_object	*obj;

	if (ft_tablen(line_tokens) != 4)
		parse_error_msg(ERROR_PARSE_TOO_MANY);
	obj = scene_new_object(glob);
	obj->shape_e = SPHERE;
	obj->shape.sphere = parse_sphere(line_tokens);
	obj->get_colision = &get_sphere_colision;
}
