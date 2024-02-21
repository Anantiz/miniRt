/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:07:30 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 12:08:38 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "libft.h"

typedef	struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

/* VECTOR OPERATOR */

t_vector			*new_vector(float x, float y, float z);
t_vector			*addition(t_vector *v1, t_vector *v2);
float				vector_length(t_vector *vector);
void				vector_normalizer(t_vector *vector);
float				vec_dot_product(t_vector *v1, t_vector *v2);

#endif