/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkary-po <lkary-po@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:07:30 by aurban            #+#    #+#             */
/*   Updated: 2024/02/21 12:09:07 by lkary-po         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "libft.h"

typedef	struct s_vector
{
	float	x;
	float	y;
	float	z;
}           t_vector;

/* VECTOR OPERATOR */

t_vector    *new_vector(float x, float y, float z);
t_vector	*addition(t_vector *v1, t_vector *v2);
float		vector_length(t_vector *vector);
void		vector_normalizer(t_vector *vector);
float		vec_dot_product(t_vector *v1, t_vector *v2);

#endif