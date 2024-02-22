/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:12:58 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 11:07:21 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

int	parse_ambiant(t_glob *glob, char **line_tokens)
{
	static bool	ambiant_set = false;

	if (ambiant_set)
		return (GO_FUCK_YOURSELF);
	ambiant_set = true;
	glob->scene->ambiant_rgb;
}