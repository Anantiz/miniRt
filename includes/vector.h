#ifndef VECTOR_H
# define VECTOR_H

// more like our own math.h

# include <math.h>
# include "libft.h"
# include "forward_declaration.h"

# define M_PI		3.14159265358979323846
# define EPSILON	0.001


// Cuz floats are faster than doubles
typedef	struct	s_vector
{
	float	x;
	float	y;
	float	z;
}t_vector;

/* VECTOR OPERATOR */

void				print_vector(t_vector *vector);

void				rea_v(t_vector **old_addr, t_vector *new_ptr);
t_vector			*new_vector(float x, float y, float z);
t_vector			*cpy_vector(t_vector *v);
t_vector			*sub_vector(t_vector *v1, t_vector *v2);
t_vector			*add_vector(t_vector *v1, t_vector *v2);
float				vector_length(t_vector *vector);
void				vector_normalizer(t_vector *vector);
float				vec_dot_product(t_vector *v1, t_vector *v2);
float				dist_vector(const t_vector *v1, const t_vector *v2);
t_vector			*mult_vector(float k, t_vector *v1);
t_vector			*produit_vectoriel(t_vector *v1, t_vector *v2);
bool				vec_cmp(t_vector *v1, t_vector *v2);

float				vec_get_angle_rad(t_vector *v1, t_vector *v2);

// float compare
bool				fcmp(float a, float b);
float				ft_bound_float(float value, float max, float min);

bool				quadratic_solver\
(t_pair_float *t, t_vector *dist_oc, t_vector *dir, float r);

#endif