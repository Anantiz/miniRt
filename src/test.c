#include "miniRt.h"


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
	t_collision	*collision;
	t_ray		ray;



	printf("Test 1:\n");
	ray.origin = new_vector(-50, 0, 0);
	ray.direction = new_vector(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);

	printf("Test 2:\n");
	ray.origin = new_vector(-50, 20, 0);
	ray.direction = new_vector(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	printf("Test 2 miss:\n");
	ray.origin = new_vector(-50, 21, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(ray.origin);
	our_free(collision);
	our_free(ray.direction);


	printf("Test 3:\n");
	ray.origin = new_vector(-50, 10, 10);
	ray.direction = new_vector(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);

	printf("Test 4:\n");
	ray.origin = new_vector(-50, 10, -10);
	ray.direction = new_vector(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);
}
