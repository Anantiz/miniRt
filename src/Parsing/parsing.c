/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:33:58 by aurban            #+#    #+#             */
/*   Updated: 2024/03/18 11:15:24 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Because we are not in the mood for error handling
	Just go F yourself if you don't like that the mandatory part and the bonus
	part of the project are not separated, if I can do more, it means I can do
	less, and it's just to fucking annoying to turn-in two different binary,
	with one being a shittier verison of the other one.

	Update: I think It might still be easily fixed with a define
*/

#include "miniRt.h"

typedef void	(*t_parse_token)(t_glob *, char **);

// Calls sub-functions to handle
static int	parse_line(t_glob *glob, const char *line)
{
	static const char			*token_types[] = {"A", "C", "L", NULL}; // Only non-object tokens
	static const t_parse_token	parsing_func[] = \
	{parse_ambiant, parse_camera, parse_light,NULL};
	char						**tokens;
	t_object 					*obj;
	int							i;

	tokens = ft_split_spaces(line);
	if (!tokens || !*tokens)
		return (SUCCESS);
	i = -1;
	while (token_types[++i])
	{
		if (!ft_strcmp(*tokens, token_types[i]))
			return ((parsing_func[i])(glob, tokens), SUCCESS);
	}
	obj = new_object(tokens);
	if (!obj)
		return (GO_FUCK_YOURSELF);
	scene_add_object(glob->scene, obj);
	return (SUCCESS);
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

static int	validate_parsing(t_glob *glob)
{
	if (glob->scene->amb_intensity < 0)
	{
		printf("\033[32mAmbiant light not set, make sure it is intentional"\
		" do so.\033[0m\n");
		glob->scene->amb_intensity = 0.0f;
	}
	if (glob->camera == NULL)
	{
		printf("\033[101mCamera not set, please do so.\033[0m\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	parse_map(t_glob *glob, char *path)
{
	char	*line;
	int		fd;
	int		line_count;

	fd = open_file(path);
	if (fd == -1)
		return (GO_FUCK_YOURSELF);
	gc_add_fd(fd);
	line = NULL;
	line_count = 0;
	while (true)
	{
		line_count++;
		ft_replace_str(&line, get_next_line(fd, false));
		if (!line)
			break ;
		if (*line == '#' || ft_is_blank_str(line))
			continue ;
		if (parse_line(glob, line) == GO_FUCK_YOURSELF)
			error_exit(ft_strjoin("Invalid parameter found on line ", \
			ft_itoa(line_count)));
	}
	gc_close_fd(fd);
	return (validate_parsing(glob));
}
