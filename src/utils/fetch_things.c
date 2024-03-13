/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:43:12 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 10:45:12 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

t_glob	*fetch_glob(t_glob *glob)
{
	static t_glob	*glob_ptr = NULL;
	if (glob)
		glob_ptr = glob;
	return (glob_ptr);
}

t_scene	*fetch_scene(t_scene *scene)
{
	static t_scene	*static_scene = NULL;

	if (scene != NULL)
		static_scene = scene;
	return (static_scene);
}

