/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:03:56 by aurban            #+#    #+#             */
/*   Updated: 2024/02/22 10:53:03 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
# define PAIR_H

# include "libft.h"

typedef struct s_pair_char
{
	char	*key;
	char	*val;
}t_pair_char;

typedef struct s_pair_void
{
	void	*first;
	void	*second;
}t_pair_void;

typedef struct s_pair_size
{
	int		width;
	int		height;
}t_pair_size;

void			pair_mfree(void *pair);
t_pair_char		*pair_char_strtok(char *str, char sep);

#endif