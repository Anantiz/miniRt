CC:=cc
INCLUDE_PATH=./includes
CFLAGS:=-Wall -Wextra -Werror -g3 -I$(INCLUDE_PATH)
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

SRC_FILES:=main.c camera/camera.c

3D_OBJ_PATH:=3D_Objects
3D_OBJ_FILES:=_3Dobj.c colider.c sphere.c plane.c cylinder.c penguin.c \
fighter_jet.c
SRC_FILES+=			$(addprefix $(3D_OBJ_PATH)/,$(3D_OBJ_FILES))

PARSE_PATH:=Parsing
PARSE_FILES:=parsing.c parsing_utils.c parsing_upper.c
SRC_FILES+=			$(addprefix $(PARSE_PATH)/,$(PARSE_FILES))

HOOK_PATH:=Hooks
HOOK_FILES:=CaptainHook.c
SRC_FILES+=			$(addprefix $(HOOK_PATH)/,$(HOOK_FILES))

RENDER_PATH:=Reindeer
RENDER_FILES:=RTT_render.c
SRC_FILES+=			$(addprefix $(RENDER_PATH)/,$(RENDER_FILES))

MATHS_PATH:=maths
MATHS_FILES:=vector_op.c vector_op2.c light_op.c
SRC_FILES+=			$(addprefix $(MATHS_PATH)/,$(MATHS_FILES))

SCENE_PATH:=scene
SCENE_FILES:= scene.c scene_services.c obj_ll.c obj_ll2.c
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
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/libmlx42.a $(BIN_LIBMLX)
	@echo "libmlx42.a created\n\n\n"

$(BIN_LIBFT):
	@make -C $(LIBFT_PATH) all
	@mv $(LIBFT_PATH)/libft.a $(BIN_LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(BIN_LIBMLX) $(BIN_LIBFT)
	$(CC) -Llibs -lft -lmlx42 -ldl -pthread -lglfw $^ -o $@ $(CFLAGS) -lm

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

.PHONY: all clean fclean re