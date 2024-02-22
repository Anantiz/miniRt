/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:33:58 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 20:04:04 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Because we are not in the mood for error handling
	Just go F yourself if you don't like that the mandatory part and the bonus
	part of the project are not separated, if I can do more, it means I can do
	less, and it's just to fucking annoying to turn-in two different binary,
	with one being a shittier verison of the other one.
*/

#include "miniRt.h"

typedef int	(*t_parse_token)(t_scene *, char **);

// Calls sub-functions to handle
static int	parse_line(t_scene *scene, const char *line)
{
	static const char			*token_types[] = \
	{"A", "C", "L", "cl", "sp", "pl", NULL};
	static const t_parse_token	parsing_func[] = \
	{parse_ambiant, parse_camera, parse_light, parse_cylinder, parse_sphere, \
	parse_plane, NULL};
	char						**tokens;
	int							i;

	ft_split_spaces(line);
	if (!line || !*line)
		return (0);
	i = -1;
	while (token_types[++i])
	{
		if (ft_strcmp(*line, token_types[i]))
			continue ;
		else
			return ((parsing_func[i])(scene, tokens));
	}
	return (GO_FUCK_YOURSELF);
}

static int	open_file(char *path)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(path, '.');
	if (ft_strcmp(extension, ".rt"))
	{
		printf("\033[41mInvalid File, scenes must have `.rt' "\
		"as an extension\033[0m\n");
		return (GO_FUCK_YOURSELF);
	}
	fd = open(path, R_OK);
	if (fd == -1)
		printf("\033[41mInvalid File: \033[0m%s\n", strerror(errno));
	return (fd);
}

int	parse_map(t_scene *scene, char *path)
{
	char	*line;
	int		fd;

	fd = open_file(path);
	if (fd == GO_FUCK_YOURSELF)
		return (GO_FUCK_YOURSELF);
	while (true)
	{
		line = get_next_line(fd, false);
		if (!line)
			break ;
		if (*line == '#' || ft_is_blank_str(line))
			continue ;
		if (parse_line(scene, line) == GO_FUCK_YOURSELF)
		{
			printf("\033[41mInvalid Token found in scene parsing\n\033[0m");
			return (GO_FUCK_YOURSELF);
		}
		our_free(line);
	}
	close(fd);
	return (SUCCESS);
}

/*
x, y ecrans
get_pixel_color(start= y, x ,0)
{
	objet[], colide_point[] = get_colision(start, direction)
	if (colide_point)
		get_colision(colide_point, diretion(du coup tu la change en focntion de refraction et bullshit comme ca))
	ray.color = moyenne (des trucs, leurs couler + intensite)
}
*/