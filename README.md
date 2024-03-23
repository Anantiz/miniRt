Current state:

VECTORS:
	-Just continue Using vectors as u are doing now:
	-At the end, put them all on the stack instead of using slow dynamic memory

DYNAMIC MEMORY:
	- USE a balanced binary tree optimized for search insertion and deletion
	- Tree optimization:
		When memory is freed:
			Free the value and put it to NULL
			Keep the Node
		When memory is requested, Look for an available Node that has NULL value
			Put your new pointer inside of it.


MEMOISATION:
	Identify redendant calculation with similar result
		Compute and cache them in the csg struct


CAMERA:
	You have pitch and yaw
	And ROLL.

	Make A plane gameplay