/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:33:58 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 18:49:19 by aurban           ###   ########.fr       */
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

/*

Parsing strategy:

	-Isolate the token Identifier:
		"A" is for Ambiant light "C" is for Camera etc...
	-


*/

static int	open_file(char *path)
{
	char	*extension;
	int		fd;

	extension = ft_strrchr(path, '.');
	if (ft_strcmp(extension, ".rt"))
	{
		printf("\033[41mInvalid File, scenes must have `.rt' as an extension\033[0m\n");
		return (GO_FUCK_YOURSELF);
	}
	fd = open(path, R_OK);
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
		line = get_next_line(fd);
		if (!line)
			break ;

	}
	close(fd);
	return (SUCCESS);
}