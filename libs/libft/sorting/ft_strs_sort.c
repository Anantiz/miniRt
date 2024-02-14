/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 10:02:01 by aurban            #+#    #+#             */
/*   Updated: 2024/02/07 10:06:47 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Ugly bubble sort for a string list
*/
char	**ft_strs_sort(char **str_tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str_tab[i])
	{
		j = i + 1;
		while (str_tab[j])
		{
			if (ft_strcmp(str_tab[i], str_tab[j]) > 0)
			{
				tmp = str_tab[i];
				str_tab[i] = str_tab[j];
				str_tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (str_tab);
}
