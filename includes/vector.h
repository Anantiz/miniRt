#ifndef VECTOR_H
# define VECTOR_H

// more like our own math.h

# include <math.h>
# include "libft.h"
# include "forward_declaration.h"

# define M_PI		3.14159265358979323846
# define M_PI_2		1.57079632679489661923
# define M_PI_4		0.78539816339744830962
# define EPSILON	0.0001

// Cuz doubles are faster than doubles
typedef	struct	s_vector
{
	double	x;
	double	y;
	double	z;
}t_vector;

/* VECTOR OPERATOR */

//v1

t_vector			*vec_new(double x, double y, double z);
t_vector			*vec_copy(t_vector *v);
t_vector			*vec_realloc(t_vector **old_addr, t_vector *new_ptr);
double				vec_dot_product(t_vector *v1, t_vector *v2);
t_vector			*vec_cross_product(t_vector *v1, t_vector *v2);

// v2

t_vector			*vec_add(t_vector *v1, t_vector *v2);
t_vector			*vec_sub(t_vector *v1, t_vector *v2);
t_vector			*vec_mult(double k, t_vector *v1);
t_vector			*vec_div(double k, t_vector *v1);
double				vec_dist(t_vector *v1, t_vector *v2);

// In place
t_vector			*vec_add_inplace(t_vector *v1, t_vector *v2);
t_vector			*vec_sub_inplace(t_vector *v1, t_vector *v2);
t_vector			*vec_mult_inplace(double k, t_vector *v1);
t_vector			*vec_div_inplace(double k, t_vector *v1);

//v3

void				vec_abs(t_vector *v);
t_vector			*vec_negate(t_vector *v);
double				vec_len(t_vector *vector);
void				vec_normalize(t_vector *vector);
bool				vec_cmp(t_vector *v1, t_vector *v2);

//v4 ++

t_vector			*vec_get_ortho(t_vector *v);
double				vec_get_angle_axis(t_vector *v1, t_vector *v2);
t_vector			*vec_project(t_vector *a, t_vector *b);

//v5

bool				vec_less_than(t_vector *a, t_vector *b);
bool				vec_more_than(t_vector *a, t_vector *b);
bool				vec_less_than_or_equal(t_vector *a, t_vector *b);
bool				vec_more_than_or_equal(t_vector *a, t_vector *b);

// double compare

bool				ft_fcmp(double a, double b);
double				ft_bound_double(double value, double max, double min);

// Just math

bool				quadratic_solver(double a, double b, double c, \
t_pair_double *t);

// Rotation

t_vector			mtx_rotate_x(t_vector *v, float angle);
t_vector			mtx_rotate_y(t_vector *v, float angle);
t_vector			mtx_rotate_z(t_vector *v, float angle);

// Shitty onces
t_vector			*vec_matrix_rotate(t_vector *v, double theta[3]);
t_vector			*vec_matrix_rev_rotate(t_vector *v, double theta[3]);
void				vec_allign_zaxis(double theta[3], t_vector *v);

// Others

double				smallest_pos(double a, double b);
void				print_vector(t_vector *vector);

// By copy

t_vector			vadd(t_vector *v1, t_vector *v2);
t_vector			vsub(t_vector *v1, t_vector *v2);
t_vector			vmult(t_vector *v1, double k);
t_vector			vdiv(t_vector *v1, double k);

// To free multiple vectors at once, cleaner than multiple calls to free
void				free2(void *v1, void *v2);
void				free3(void *v1, void *v2, void *v3);
void				free4(void *v1, void *v2, void *v3,  void *v4);

#endif