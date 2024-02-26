#include "miniRt.h"

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

// void	my_test(t_glob *glob)
// {
// 	(void)glob;
// 	/*

// 		TEST 1:
// 		- Create a sphere (already parsed)
// 			-origin: 0, 0, 0
// 			-radius: 10
// 		- Create a ray
// 		- Test the collision between the sphere and the ray
// 	*/
// 	t_collision	*collision;


// 	// Is aimed towards the origin of the sphere
// 	t_ray		ray_hit;
// 	t_vector	origin_hit = {-10, 1, 0};
// 	t_vector	direction_hit = {1, 0, 0};
// 	ray_hit.origin = &origin_hit;
// 	ray_hit.direction = &direction_hit;
// 	printf("\033[32mTest 1: Sphere collision\033[0m\n");
// 	/*
// 		Expected :
// 			Collision distance: 40
// 			Collision point: x:-10.00 y:0.00, z: 0.00
// 	*/
// 	collision = scene_collision_query(glob->scene, &ray_hit);
// 	print_collision(collision);
// 	our_free(collision);


// 	// Same as the first test, but the sphere is behind
// 	t_ray		ray_miss;
// 	t_vector	origin_miss = {100, 0, 0};
// 	t_vector	direction_miss = {1, 0, 0};
// 	ray_miss.origin = &origin_miss;
// 	ray_miss.direction = &direction_miss;
// 	printf("\033[32mTest 2: Sphere no collision\033[0m\n");
// 	collision = scene_collision_query(glob->scene, &ray_miss);
// 	print_collision(collision);
// 	our_free(collision);

// 	// Is aimed below the sphere
// 	t_vector	origin_miss2 = {-100, 0, 0};
// 	t_vector	direction_miss2 = {1, 0, 0};
// 	ray_miss.origin = &origin_miss2;
// 	ray_miss.direction = &direction_miss2;
// 	printf("\033[32mTest 3: Sphere no collision\033[0m\n");
// 	collision = scene_collision_query(glob->scene, &ray_miss);
// 	print_collision(collision);
// 	our_free(collision);
// 	/*
// 		Result:

// 		It seems like it actually works fine but in the wrong direction
// 	*/
// }
