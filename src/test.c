#include "miniRt.h"

void	get_angles_for_matrix(double theta[3], t_vector *v)
{
	// Currently if we do it only once it won't work
	// But if we reapply the rotation it will work
	theta[1] = -atan2(v->x, v->z);
	theta[0] = atan2(v->y, v->z);
	theta[2] = 0;
	// So find a way to make it work
}

void	my_test(t_glob *glob)
{
	(void)glob;
	/*

		TEST 1:
		- Create a sphere (already parsed)
			-origin: 0, 0, 0
			-radius: 10
		- Create a ray
		- Test the collision between the sphere and the ray
	*/
	printf("\033[33m");
	t_vector	*ret;
	t_vector	vx = (t_vector){1, 0, 0};
	t_vector	vy = (t_vector){0, 1, 0};
	t_vector	vz = (t_vector){0, 0, 1};
	t_vector	vxy = (t_vector){1, 1, 0};
	double		theta[3];

	vec_normalize(&vx);
	vec_normalize(&vy);
	vec_normalize(&vz);
	vec_normalize(&vxy);

	// Test rotating x on z-axis
	printf("Test 1:\n");
	// theta[0] = 0;
	// theta[1] = -(M_PI / 2);
	// theta[2] = 0;
	vec_allign_zaxis(theta, &vx);
	printf("Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("Before rotation:\t");
	print_vector(&vx);
	printf("After rotation :\t");
	ret = vec_matrix_rotate(&vx, theta);
	vec_normalize(ret);
	print_vector(ret);
	printf("\n");
	our_free(ret);

	// Test rotating y on z-axis
	printf("Test 2:\n");
	// theta[0] = (M_PI / 2);
	// theta[1] = 0;
	// theta[2] = 0;
	vec_allign_zaxis(theta, &vy);
	printf("Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("Before rotation:\t");
	print_vector(&vy);
	printf("After rotation :\t");
	ret = vec_matrix_rotate(&vy, theta);
	vec_normalize(ret);
	print_vector(ret);
	printf("\n");
	our_free(ret);

	// Test rotating z on z-axis
	printf("Test 3:\n");
	// theta[0] = 0;
	// theta[1] = 0;
	// theta[2] = 0;
	vec_allign_zaxis(theta, &vz);
	printf("Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("Before rotation:\t");
	print_vector(&vz);
	printf("After rotation :\t");
	ret = vec_matrix_rotate(&vz, theta);
	vec_normalize(ret);
	print_vector(ret);
	printf("\n");
	our_free(ret);

	// Test rotating xy on z-axis
	printf("Test 4:\n");

	vec_allign_zaxis(theta, &vxy);
	printf("1-Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("\t1-Before rotation:\t");
	print_vector(&vxy);
	printf("\t1-After rotation :\t");
	ret = vec_matrix_rotate(&vxy, theta);
	vec_normalize(ret);
	print_vector(ret);

	vec_allign_zaxis(theta, ret);
	printf("2-Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("\t2-Before rotation:\t");
	print_vector(ret);
	printf("\t2-After rotation :\t");
	vec_realloc(&ret, vec_matrix_rotate(ret, theta));
	vec_normalize(ret);
	print_vector(ret);

	our_free(ret);
	printf("\n");

	// Alling An xyz vector to z axis
	printf("Test 5:\n");
	t_vector	xyz = (t_vector){1, 1, 1};
	vec_normalize(&xyz);

	vec_allign_zaxis(theta, &xyz);
	printf("1-Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("\t1-Before rotation:\t");
	print_vector(&xyz);
	printf("\t1-After rotation :\t");
	ret = vec_matrix_rotate(&xyz, theta);
	vec_normalize(ret);
	print_vector(ret);

	vec_allign_zaxis(theta, ret);
	printf("2-Euler Angles   :\t %fx %fy %fz\n", theta[0], theta[1], theta[2]);
	printf("\t2-Before rotation:\t");
	print_vector(ret);
	printf("\t2-After rotation :\t");
	vec_realloc(&ret, vec_matrix_rotate(ret, theta));
	vec_normalize(ret);
	print_vector(ret);

	our_free(ret);
	printf("\n");


	printf("TEST DONE\033[0m\n\n\n");
}
