#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include "libft.h"

// Cuz floats are faster than doubles
typedef	struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

/* VECTOR OPERATOR */

void				rea_v(t_vector **old_addr, t_vector *new_ptr);
t_vector			*new_vector(float x, float y, float z);
t_vector			*cpy_vector(t_vector *v);
t_vector			*sub_vector(t_vector *v1, t_vector *v2);
t_vector			*add_vector(t_vector *v1, t_vector *v2);
float				vector_length(t_vector *vector);
void				vector_normalizer(t_vector *vector);
float				vec_dot_product(t_vector *v1, t_vector *v2);
float				dist_vector(const t_vector *v1, const t_vector *v2);

#endif