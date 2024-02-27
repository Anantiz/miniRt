#include "miniRt.h"

void	print_rgb(t_rgb *color)
{
	if (color)
		printf(" %3d r, %3d g, %3d b\n", color->r, color->g, color->b);
	else
		printf("NULL\n");
}

void	print_vector(t_vector *vector)
{
	if (vector)
		printf(" %8.2f x, %8.2f y, %8.2f z\n", vector->x, vector->y, vector->z);
	else
		printf("NULL\n");
}

void	print_collision(t_collision *collision)
{
	static const char		*shape_names[] = {"Sphere", "Plane", "Cylinder"};

	if (collision)
	{
		printf("Collision Object: ");
		printf("%s\n", shape_names[collision->obj->type]);
		printf("Collision detected at distance: %8.2f\n", collision->dist);
		printf("Collision point: ");
		print_vector(&collision->point);
	}
	else
		printf("No collision detected\n");
	printf("\n");
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
	t_collision	*collision;
	t_ray		ray;



	printf("Test 1:\n");
	ray.origin = new_vector(-50, 0, 0);
	ray.direction = new_vector(1, 0, 0);
	collision = query_obj_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);

	printf("Test 2:\n");
	ray.origin = new_vector(-50, 20, 0);
	ray.direction = new_vector(1, 0, 0);
	collision = query_obj_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	printf("Test 2 miss:\n");
	ray.origin = new_vector(-50, 21, 0);
	collision = query_obj_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(ray.origin);
	our_free(collision);
	our_free(ray.direction);


	printf("Test 3:\n");
	ray.origin = new_vector(-50, 10, 10);
	ray.direction = new_vector(1, 0, 0);
	collision = query_obj_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);

	printf("Test 4:\n");
	ray.origin = new_vector(-50, 10, -10);
	ray.direction = new_vector(1, 0, 0);
	collision = query_obj_collision(glob->scene, &ray);
	print_collision(collision);
	our_free(collision);
	our_free(ray.origin);
	our_free(ray.direction);
}
