/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CaptainHook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:16:39 by aurban            #+#    #+#             */
/*   Updated: 2024/03/25 11:35:33 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

#define MOVE_SPEED 8
#define CAM_ROTATE_SPEED 0.1
/*
	dir_sign:
		1: forward
		-1: backward
*/
static void	move_camera(t_glob *g, t_vector *camera_pos, t_vector *dir, int dir_sign)
{
	if (g->update == true) // We don't want to move the camera while rendering
		return ;
	g->update = true;
	camera_pos->x += (dir->x * dir_sign) * MOVE_SPEED;
	camera_pos->y += (dir->y * dir_sign) * MOVE_SPEED;
	camera_pos->z += (dir->z * dir_sign) * MOVE_SPEED;
}

static void rotate_camera(t_glob *g, t_vector *camera_dir, t_vector *dir, int dir_sign)
{
	if (g->update == true) // We don't want to move the camera while rendering
		return ;
	g->update = true;
	// Also, we should not actually add the dir to the camera_dir
	// We should rotate the existing one by a certain amount (Fixed angle by key press)
	camera_dir->x += (dir->x * dir_sign) * CAM_ROTATE_SPEED;
	camera_dir->y += (dir->y * dir_sign) * CAM_ROTATE_SPEED;
	camera_dir->z += (dir->z * dir_sign) * CAM_ROTATE_SPEED;
	// TO DO: Update the right and up vectors
	// camera_update_right_up(g->camera);
}

static void roll_camera(t_glob *g, t_camera *cam, int dir_sign)
{
	(void)cam;
	(void)dir_sign;
	if (g->update == true) // We don't want to move the camera while rendering
		return ;
	g->update = true;

	// TO DO:MAKE A FUNCTION TO ROTATE A VECTOR AROUND ANOTHER VECTOR
	// cam->up = vec_matrix_rotate(cam->up, cam->dir, dir_sign * M_PI_4);
	// cam->right = vec_matrix_rotate(cam->right, cam->dir, dir_sign * M_PI_4);
}


static void	cptn_hook_key2(t_glob *glob, mlx_key_data_t keydata);

void	cptn_hook_key(mlx_key_data_t keydata, void *glob_)
{
	t_glob	*glob;

	glob = (t_glob *)glob_;
	if (keydata.action == MLX_RELEASE)
		return ;
	else if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(glob->mlx);
	// WASD to move front, back, left and right
	if (keydata.key == MLX_KEY_W)
		move_camera(glob, glob->camera->pos, glob->camera->dir, 1);
	else if (keydata.key == MLX_KEY_S)
		move_camera(glob, glob->camera->pos, glob->camera->dir, -1);
	else if (keydata.key == MLX_KEY_A)
		move_camera(glob, glob->camera->pos, glob->camera->right, -1);
	else if (keydata.key == MLX_KEY_D)
		move_camera(glob, glob->camera->pos, glob->camera->right, 1);
	else
		cptn_hook_key2(glob, keydata);
}

static void	cptn_hook_key2(t_glob *glob, mlx_key_data_t keydata)
{
	// SPACE and CTRL to move up and down
	if (keydata.key == MLX_KEY_SPACE)
		move_camera(glob, glob->camera->pos, glob->camera->up, -1);
	else if (keydata.key == MLX_KEY_LEFT_CONTROL)
		move_camera(glob, glob->camera->pos, glob->camera->up, 1);

	// Arrow keys to rotate the camera
	else if (keydata.key == MLX_KEY_LEFT)
		rotate_camera(glob, glob->camera->dir, glob->camera->right, -1);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate_camera(glob, glob->camera->dir, glob->camera->right, 1);
	else if (keydata.key == MLX_KEY_UP)
		rotate_camera(glob, glob->camera->dir, glob->camera->up, -1);
	else if (keydata.key == MLX_KEY_DOWN)
		rotate_camera(glob, glob->camera->dir, glob->camera->up, 1);
	// Rotate roll
	else if (keydata.key == MLX_KEY_Q)
		roll_camera(glob, glob->camera, -1);
	else if (keydata.key == MLX_KEY_E)
		roll_camera(glob, glob->camera, 1);
}
