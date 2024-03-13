/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:14:42 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 11:28:28 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

/*
	If we somehow add new things we can free them here
*/
void	del_collision(t_collision *col)
{
	// May delete the ray, depends on what we do later
	our_free(col->norm);
	our_free(col);
}

/*
	Deletes the linked list of light collisions
*/
void	del_light_col(t_lcol *lcol)
{
	if (lcol)
		del_light_col(lcol->next);
	our_free(lcol);
}
