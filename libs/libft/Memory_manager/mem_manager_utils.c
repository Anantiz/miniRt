/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:34:38 by aurban            #+#    #+#             */
/*   Updated: 2024/01/30 17:39:15 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Duplicate a string and free the original
	It allows us to use our memory to track the new string
*/
char	*unionize_str(char *theirs)
{
	char	*ours;

	ours = ft_strdup(theirs);
	free(theirs);
	return (ours);
}
