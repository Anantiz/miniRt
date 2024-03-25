/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_things.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:14:42 by aurban            #+#    #+#             */
/*   Updated: 2024/03/25 12:00:10 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRt.h"

/*
	If we somehow add new things we can free them here
*/
inline void	del_collision(t_collision *col)
{
	// May delete the ray, depends on what we do later
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

inline void	free2(void *v1, void *v2)
{
	our_free(v1);
	our_free(v2);
}

inline void	free3(void *v1, void *v2, void *v3)
{
	our_free(v1);
	our_free(v2);
	our_free(v3);
}

inline void	free4(void *v1, void *v2, void *v3,  void *v4)
{
	our_free(v1);
	our_free(v2);
	our_free(v3);
	our_free(v4);
}
