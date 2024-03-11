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
	ray.pos = vec_new(-50, 0, 0);
	ray.dir = vec_new(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.pos);
	our_free(ray.dir);

	printf("Test 2:\n");
	ray.pos = vec_new(-50, 20, 0);
	ray.dir = vec_new(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.pos);
	printf("Test 2 miss:\n");
	ray.pos = vec_new(-50, 21, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(ray.pos);
	our_free(collision);
	our_free(ray.dir);


	printf("Test 3:\n");
	ray.pos = vec_new(-50, 10, 10);
	ray.dir = vec_new(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.pos);
	our_free(ray.dir);

	printf("Test 4:\n");
	ray.pos = vec_new(-50, 10, -10);
	ray.dir = vec_new(1, 0, 0);
	collision = query_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.pos);
	our_free(ray.dir);
}
