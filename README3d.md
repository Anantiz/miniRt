Firstly: Separation of concern:

	The only interface between the monitor rendering and the 3D scene will be this function:

	typedef	struct s_ray
	{
		int			lumen;
		t_rgb		ray_color;

		t_vector	*origin;
		t_vector	*direction;
	}t_ray;

	scene_collision_query(t_scene scene, t_ray ray);
		returns a t_colision struct {with the collision coordinate and a pointer to the object it hit}

	As for now we are only focusing on the 3D aspect of the project.

Secondly: Our Retained Idea:
	The t_scene data-structure will hold a linked list of all objects and light sources of the scene.

	A t_object structure will be working like this:
		-The coordinates of the origing and it's orientation.
		-A binary tree to represent an object (CSG).
		-Some other data used by the ray casting engine such as:
			-Material (for refraction etc...)
			-Color + Texture
			And some other data, allowing any object to be a light source (without being a point-light)

Lastly: My current challenge
	-I have to understand and implement a way to represent 3D primitives efficiently
	-I have to come up with an algorithmic formula to quickly calculate any colisions
		.This algorithm has to "read" the CSG tree to `create' a formula to solve as an equation and find Whether it collides or not.