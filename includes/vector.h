#ifndef VECTOR_H
# define VECTOR_H

// more like our own math.h

# include <math.h>
# include "libft.h"
# include "forward_declaration.h"

# define M_PI		3.14159265358979323846
# define EPSILON	0.00001


// Cuz floats are faster than doubles
typedef	struct	s_vector
{
	float	x;
	float	y;
	float	z;
}t_vector;

/* VECTOR OPERATOR */

void				print_vector(t_vector *vector);

void				vec_realloc(t_vector **old_addr, t_vector *new_ptr);
t_vector			*vec_new(float x, float y, float z);
t_vector			*vec_cpy(t_vector *v);
t_vector			*vec_sub(t_vector *v1, t_vector *v2);
t_vector			*vec_add(t_vector *v1, t_vector *v2);
float				vec_length(t_vector *vector);
void				vec_normalize(t_vector *vector);
float				vec_dot_product(t_vector *v1, t_vector *v2);
float				vec_dist(const t_vector *v1, const t_vector *v2);
t_vector			*vec_mult(float k, t_vector *v1);
t_vector			*vec_cross_product(t_vector *v1, t_vector *v2);
bool				vec_cmp(t_vector *v1, t_vector *v2);

t_vector			*vec_get_ortho(t_vector *v);
float				vec_get_angle_rad(t_vector *v1, t_vector *v2);

// float compare
bool				fcmp(float a, float b);
float				ft_bound_float(float value, float max, float min);

bool				quadratic_solver(float a, float b, float c, \
t_pair_float *t);

#endif