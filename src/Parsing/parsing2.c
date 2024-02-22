/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 12:36:56 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

static int	parse_ambiant_rgb(t_glob *glob, char **rgb)
{
	int	i;
	int x;

	i = -1;
	if (!ft_is_int_format(rgb[0]))
		return (GO_FUCK_YOURSELF);
	x = ft_atoi(rgb[0]);
	if (x < 0 || x > 255)
		return (GO_FUCK_YOURSELF);
	glob->scene->ambiant_rgb.r = x;
	if (!ft_is_int_format(rgb[1]))
		return (GO_FUCK_YOURSELF);
	x = ft_atoi(rgb[1]);
	if (x < 0 || x > 255)
		return (GO_FUCK_YOURSELF);
	glob->scene->ambiant_rgb.g = x;
	if (!ft_is_int_format(rgb[2]))
		return (GO_FUCK_YOURSELF);
	x = ft_atoi(rgb[2]);
	if (x < 0 || x > 255)
		return (GO_FUCK_YOURSELF);
	glob->scene->ambiant_rgb.b = x;
	return (SUCCESS);
}

/*
Ambiant light rules:

- Can only be set once
- Must be a float between 0 and 1
- Must be followed by 3 int between 0 and 255 (r,g,b)
*/
int	parse_ambiant(t_glob *glob, char **line_tokens)
{
	static bool	ambiant_set = false;
	char		**rgb;

	if (ambiant_set)
		return (GO_FUCK_YOURSELF);
	ambiant_set = true;
	if (!ft_is_float_format(line_tokens[1]))
		return (GO_FUCK_YOURSELF);
	glob->scene->al_intensity = ft_atoldb(line_tokens[1]);
	if (glob->scene->al_intensity > 1 || glob->scene->al_intensity < 0)
		return (GO_FUCK_YOURSELF);
	rgb = ft_split(line_tokens[2], ',');
	if (ft_tablen(rgb) != 3)
		return (GO_FUCK_YOURSELF);
	parse_ambiant_rgb(glob, rgb);
	free_double_char(rgb);
	if (line_tokens[3] && *line_tokens[3] && *line_tokens[3] != '#')
		return (GO_FUCK_YOURSELF);
	return (SUCCESS);
}

