/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurban <aurban@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:51:00 by aurban            #+#    #+#             */
/*   Updated: 2024/03/11 10:51:43 by aurban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float		vec_get_angle_rad(t_vector *v1, t_vector *v2)
{
	static bool debug = false;
	t_vector	normed1;
	t_vector	normed2;
	float		temp;
	float		angle;

	temp = vec_length(v1);
	if (temp == 0)
		return (0);
	else
		normed1 = (t_vector){v1->x / temp, v1->y / temp, v1->z / temp};

	temp = vec_length(v2);
	if (temp == 0)
		return (0);
	else
		normed2 = (t_vector){v2->x / temp, v2->y / temp, v2->z / temp};

	temp = ft_bound_float(vec_dot_product(v1, v2), 1, -1);
	angle = temp / ft_bound_float(vec_dot_product(&normed1, &normed2), 1, -1);
	if (!debug)
	{
		debug = true;
		printf("v1:\t");
		print_vector(v1);
		printf("v2:\t");
		print_vector(v2);
		printf("v1 dot v2:   %f\n", temp);
		printf("n1 dot n2:   %f\n", vec_dot_product(&normed1, &normed2));
		printf("angle:       %f\n", angle);
	}
	if (isnan(angle))
		return (0);
	while (angle > 1)
		angle -= 1;
	while (angle < -1)
		angle += 1;
	return (acosf(angle)); // Acos cuz we want the angle, not the cosinus
}

void	vec_abs(t_vector *v)
{
	v->x = fabs(v->x);
	v->y = fabs(v->y);
	v->z = fabs(v->z);
}