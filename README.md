3D:---------
	-Function to make the shapes
	-Camera
	-Scene

Parsing:
	-String comparaison (so fun !!!!)

Ray-Tracing:
	-Ray casting
	-Collision detection
	-Refraction/reflection/difraction and shit like that

BONUS:
	-Bump map textures
	-Miroir
	-Prisme (Dispersion) (impeu difficileu)


Separation of Concern:
	src/maths/
		General functions to perform arithmetic on the data

	src/ray/
		The algorithmique implementation to cast rays
		and trace them back recursively until a light source

	src/scene
		Hold function to create a Scene, and to create objects
		Provides Utility function for the src/ray algo
			Utilities function to provide:
				-scene_collision_query(t_vector origin, t_vector direction);
					returns a t_colision struct {with the collision coordinate
					and a pointer to the object it hit}


Theory des rebonds:

LOOP:
	RAY_GUN go pew pew
		pew pew hit smthing
	Call RAY_GUN again on the coordinate you hit (until MAX_recursion is REACHED)

	Once you reached the return condition
		-> Create A struct (RAY_PATH)
		Returns the same one (RAY_PATH) along all the calls.
	In this structure you will store all the measured collisions (as a t_collision *arr[obj_count] and ray)
	And also some other random data.

	Then once it's all returned call the put_pixel() function that will calculate the
	pixel color accordingly (using all the data stored in the streuct)