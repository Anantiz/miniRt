#ifndef FORWARD_DECLARATION_H
# define FORWARD_DECLARATION_H

// Global shared data-structures

typedef struct s_camera				t_camera;
typedef struct s_glob				t_glob;

// Math

typedef struct s_vector				t_vector;
typedef struct s_ray				t_ray;

// Colors & Materials

typedef struct s_color				t_color;
typedef struct s_material			t_material;


// Light

typedef struct s_light				t_light;
typedef struct s_object				t_object;
typedef struct s_spot_light			t_spot_light;
typedef t_spot_light				t_slight;

// Objects

typedef struct s_collision			t_collision;

typedef enum e_objtype				t_objtype;
typedef enum e_primitive			t_e_prim;
typedef enum e_ndtype				t_e_ndtype;

typedef struct s_csg				t_csg;
typedef struct s_object				t_object;

typedef struct s_csg_leave			t_csg_leave;
typedef union u_shape				t_u_shape;

// Scene

typedef struct s_scene				t_scene;
typedef struct s_ll_obj				t_ll_obj;

#endif