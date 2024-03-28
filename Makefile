CC:=cc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -O3 -pg -I$(INCLUDE_PATH) #-fsanitize=address
RM:=rm -rf

NAME:=miniRt

SRC_PATH:=./src
OBJ_PATH:=./objs

LIBMLX_PATH		:=./libs/MLX42
BIN_LIBMLX		:=./libs/libmlx42.a

LIBFT_PATH		:=./libs/libft
BIN_LIBFT		:=./libs/libft.a

###############################################################
#	####	####	####	####	####	####	####	####
#		####	####	####	SRC 	####	####	####	#
#	####	####	####	####	####	####	####	####
###############################################################

SRC_FILES:=main.c test.c

UTILS_PATH:=utils
UTILS_FILES:=colors.c print_shit.c delete_things.c fetch_things.c
SRC_FILES+=			$(addprefix $(UTILS_PATH)/,$(UTILS_FILES))

COLLIDER_PATH:=3D_Objects/Collider
COLLIDER_FILES:=collider2.c collider.c collision_norm.c csg_utils.c
SRC_FILES+=			$(addprefix $(COLLIDER_PATH)/,$(COLLIDER_FILES))

_OBJS_PATH:=3D_Objects/Objs
_OBJS_FILES:=obj_sphere.c obj_plane.c obj_cylinder.c obj_penguin.c obj_fighter_jet.c\
obj_cone.c
SRC_FILES+=			$(addprefix $(_OBJS_PATH)/,$(_OBJS_FILES))

3D_OBJ_PATH:=3D_Objects
3D_OBJ_FILES:=_3Dobj.c pr_sphere.c pr_plane.c pr_cylinder.c pr_helpers.c \
pr_cone.c
SRC_FILES+=			$(addprefix $(3D_OBJ_PATH)/,$(3D_OBJ_FILES))

PARSE_PATH:=Parsing
PARSE_FILES:=parsing.c parsing_utils.c parsing_upper.c parsing_utils2.c\
parsing_camera.c
SRC_FILES+=			$(addprefix $(PARSE_PATH)/,$(PARSE_FILES))

HOOK_PATH:=Hooks
HOOK_FILES:=CaptainHook.c
SRC_FILES+=			$(addprefix $(HOOK_PATH)/,$(HOOK_FILES))

RAY_PATH:=ray
RAY_FILES:=ray_gun.c ray_bounce.c
SRC_FILES+=			$(addprefix $(RAY_PATH)/,$(RAY_FILES))

RENDER_PATH:=Reindeer
RENDER_FILES:=RTT_render.c
SRC_FILES+=			$(addprefix $(RENDER_PATH)/,$(RENDER_FILES))

MATHS_PATH:=maths
MATHS_FILES:=vector_op.c vector_op2.c vector_op3.c vector_op4.c light_op.c \
quadratic_solver.c get_orthogonal.c math_utils.c vector_op5.c vector_op2inplace.c \
project.c matrix.c matrix2.c vector_op22.c
SRC_FILES+=			$(addprefix $(MATHS_PATH)/,$(MATHS_FILES))

SCENE_PATH:=scene
SCENE_FILES:= scene.c scene_services.c obj_ll.c obj_ll2.c light.c
SRC_FILES+=			$(addprefix $(SCENE_PATH)/,$(SCENE_FILES))

SRC_FILES:=			$(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJ:=			$(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o,$(SRC_FILES))

###############################################################
#	####	####	####	####	####	####	####	####
#		####	####	####	Rules 	####	####	####	#
#	####	####	####	####	####	####	####	####
###############################################################

all: $(NAME)

$(BIN_LIBMLX):
	cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -sC $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/libmlx42.a $(BIN_LIBMLX)
	@echo "libmlx42.a created\n\n\n"

$(BIN_LIBFT):
	@make -sC $(LIBFT_PATH) all
	@mv $(LIBFT_PATH)/libft.a $(BIN_LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(BIN_LIBMLX) $(BIN_LIBFT)
	@$(CC) -Llibs -lft -lmlx42 -ldl -pthread -lglfw -lm $^ -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJ_PATH)
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(LIBMLX_PATH)/build
	@$(RM) $(LIBMLX_PATH)/CmakeFiles

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BIN_LIBFT)
	@$(RM) $(BIN_LIBMLX)

re: fclean all

redo: clean all

.PHONY: all clean fclean re cldo

