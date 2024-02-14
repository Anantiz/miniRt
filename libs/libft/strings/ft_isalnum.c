/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:54:41 by aurban            #+#    #+#             */
/*   Updated: 2024/02/13 11:14:23 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

/* In this file cuz fck it*/
char	*ft_chardup(char c)
{
	char	*str;

	str = our_malloc(2);
	str[0] = c;
	str[1] = 0;
	return (str);
}
