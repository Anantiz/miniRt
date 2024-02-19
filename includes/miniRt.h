/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 00:24:18 by aurban            #+#    #+#             */
/*   Updated: 2024/02/19 13:51:08 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>

# include "../libs/MLX42/include/MLX42/MLX42_Int.h"
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
