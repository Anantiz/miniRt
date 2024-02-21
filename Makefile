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

#########################################################
#	####	####	####	####	####	####		#
#		####	####	SRCS 	####	####	####	#
#	####	####	####	####	####	####		#
#########################################################

SRC_FILES:=main.c maths/vector_op.c

SCENE_PATH:=scene
SCENE_FILES:=cube.c sphere.c plane.c cylinder.c cone.c
SRC_FILES+=			$(addprefix $(SCENE_PATH)/,$(SCENE_FILES))

SRC_FILES:=			$(addprefix $(SRC_PATH)/,$(SRC_FILES))
SRC_OBJ:=			$(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o,$(SRC_FILES))

#########################################################
#	####	####	####	####	####	####		#
#		####	####	Rules 	####	####	####	#
#	####	####	####	####	####	####		#
#########################################################

all: $(NAME)

$(BIN_LIBMLX):
	@cmake $(LIBMLX_PATH) -B $(LIBMLX_PATH)/build && make -C $(LIBMLX_PATH)/build -j4
	@mv $(LIBMLX_PATH)/build/libmlx42.a $(BIN_LIBMLX)

$(BIN_LIBFT):
	@make -C $(LIBFT_PATH) all
	@mv $(LIBFT_PATH)/libft.a $(BIN_LIBFT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(BIN_LIBMLX) $(BIN_LIBFT)
	$(CC) $(CFLAGS) -lm -Llibs -lft -lmlx42 $^ -o $@

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