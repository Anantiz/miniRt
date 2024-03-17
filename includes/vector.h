#ifndef VECTOR_H
# define VECTOR_H

// more like our own math.h

# include <math.h>
# include "libft.h"
# include "forward_declaration.h"

# define M_PI		3.14159265358979323846
# define EPSILON	0.0001


// Cuz floats are faster than doubles
typedef	struct	s_vector
{
	float	x;
	float	y;
	float	z;
}t_vector;

/* VECTOR OPERATOR */

//v1

t_vector			*vec_new(float x, float y, float z);
t_vector			*vec_copy(t_vector *v);
t_vector			*vec_realloc(t_vector **old_addr, t_vector *new_ptr);
float				vec_dot_product(t_vector *v1, t_vector *v2);
t_vector			*vec_cross_product(t_vector *v1, t_vector *v2);

// v2

t_vector			*vec_add(t_vector *v1, t_vector *v2);
t_vector			*vec_sub(t_vector *v1, t_vector *v2);
t_vector			*vec_mult(float k, t_vector *v1);
t_vector			*vec_div(float k, t_vector *v1);
float				vec_dist(t_vector *v1, t_vector *v2);

// In place
t_vector			*vec_add_inplace(t_vector *v1, t_vector *v2);
t_vector			*vec_sub_inplace(t_vector *v1, t_vector *v2);
t_vector			*vec_mult_inplace(float k, t_vector *v1);
t_vector			*vec_div_inplace(float k, t_vector *v1);

//v3

void				vec_abs(t_vector *v);
t_vector			*vec_negate(t_vector *v);
float				vec_len(t_vector *vector);
void				vec_normalize(t_vector *vector);
bool				vec_cmp(t_vector *v1, t_vector *v2);

//v4 ++

t_vector			*vec_get_ortho(t_vector *v);
float				vec_get_angle_axis(t_vector *v1, t_vector *v2);
t_vector			*vec_project(t_vector *a, t_vector *b);

//v5

bool				vec_less_than(t_vector *a, t_vector *b);
bool				vec_more_than(t_vector *a, t_vector *b);
bool				vec_less_than_or_equal(t_vector *a, t_vector *b);
bool				vec_more_than_or_equal(t_vector *a, t_vector *b);

// float compare
bool				fcmp(float a, float b);
float				ft_bound_float(float value, float max, float min);

// Just math

bool				quadratic_solver(float a, float b, float c, \
t_pair_float *t);

// Others

float				smallest_pos(float a, float b);
void				print_vector(t_vector *vector);

// To free multiple vectors at once, cleaner than multiple calls to free
void				free2(void *v1, void *v2);
void				free3(void *v1, void *v2, void *v3);
void				free4(void *v1, void *v2, void *v3,  void *v4);

#endif