/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CaptainHook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:16:39 by aurban            #+#    #+#             */
/*   Updated: 2024/02/25 23:49:20 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

void	cptn_hook_key(mlx_key_data_t keydata, void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	if (keydata.action == MLX_RELEASE)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(glob->mlx);
}
