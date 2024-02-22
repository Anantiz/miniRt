# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurban <aurban@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/20 06:06:39 by aurban            #+#    #+#              #
#    Updated: 2024/02/21 19:07:16 by aurban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_NAME:=libft.a

CC:=gcc
INCLUDE_PATH= ../../includes
CFLAGS:=-Wall -Werror -Wextra -I$(INCLUDE_PATH) -g3

OBJ_PATH:=./objs

FT_FILES=

# --- MEM MANAGER ---

FT_MEM_MANAGER_PATH=Memory_manager
FT_MEM_MANAGER_FILES=ft_bzero.c	ft_calloc.c mem_manager_op.c mem_manager.c \
	mem_manager_utils.c
FT_MEM_MANAGER_FILES:=$(addprefix $(FT_MEM_MANAGER_PATH)/,$(FT_MEM_MANAGER_FILES))

# --- SORTING ---

FT_SORTING_PATH=sorting
FT_SORTING_FILES=ft_strs_sort.c
FT_SORTING_FILES:=$(addprefix $(FT_SORTING_PATH)/,$(FT_SORTING_FILES))

# --- LINKED LIST ---

FT_LINKED_LIST_PATH:=linked_list
FT_LINKED_LIST_FILES:=\
	ft_linked_list_add.c	ft_linked_list_del.c	ft_linked_list_init.c	\
	ft_linked_list_rotate.c	ft_linked_list_swap.c	ft_linked_list_utils.c
FT_LINKED_LIST_FILES:= $(addprefix $(FT_LINKED_LIST_PATH)/,$(FT_LINKED_LIST_FILES))

# --- CONVERSIONS ---

FT_CONVERSIONS_PATH:=conversions
FT_CONVERSIONS_FILES:=\
	ft_itoa.c 		ft_uitoa.c	ft_uitohex.c	ft_ltohex.c ft_atoi.c		\
	ft_ultohex.c	ft_lltoa.c	ft_atoldb.c		ft_atoll.c	ft_tolower.c	\
	ft_toupper.c	ft_max_abs.c
FT_CONVERSIONS_FILES:=$(addprefix $(FT_CONVERSIONS_PATH)/,$(FT_CONVERSIONS_FILES))

# --- PRINTF ---

FT_PRINTF_PATH=ft_printf
FT_PRINTF_FILES=ft_printf.c	ft_send_to_buffer.c	ft_arg_to_buffer.c
FT_PRINTF_FILES:=$(addprefix $(FT_PRINTF_PATH)/,$(FT_PRINTF_FILES))

# --- GET NEXT LINE ---

FT_GNL_PATH=gaz_naturel_liquefie
FT_GNL_FILES=get_next_line.c	get_next_line_utils.c
FT_GNL_FILES:=$(addprefix $(FT_GNL_PATH)/,$(FT_GNL_FILES))

# --- STRINGS ---

FT_STRINGS_PATH:=strings
FT_STRINGS_FILES=\
	ft_isalnum.c	ft_isalpha.c	ft_isdigit.c	ft_isprint.c	ft_isascii.c	\
	ft_memchr.c		ft_memcmp.c		ft_memcpy.c		ft_memmove.c	ft_memset.c		\
	ft_putchar_fd.c	ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c	ft_split.c		\
	ft_strchr.c		ft_strdup.c		ft_striteri.c	ft_strjoin.c	ft_strlcat.c	\
	ft_strlcpy.c	ft_strlen.c		ft_strmapi.c	ft_strncmp.c	ft_strnstr.c	\
	ft_strrchr.c	ft_strtrim.c	ft_substr.c		ft_str_lists.c	ft_tablen.c		\
	ft_strdup_double_char.c			ft_split_spaces.c
FT_STRINGS_FILES:=$(addprefix $(FT_STRINGS_PATH)/,$(FT_STRINGS_FILES))

# --- LIB FT ---

FT_FILES+=$(FT_LINKED_LIST_FILES)
FT_FILES+=$(FT_CONVERSIONS_FILES)
FT_FILES+=$(FT_PRINTF_FILES)
FT_FILES+=$(FT_STRINGS_FILES)
FT_FILES+=$(FT_GNL_FILES)
FT_FILES+=$(FT_MEM_MANAGER_FILES)
FT_FILES+=$(FT_SORTING_FILES)

# FT_PATH:=./
# FT_FILES:= $(addprefix $(FT_PATH)/,$(FT_FILES))
FT_OBJECTS= $(patsubst %.c,%.o,$(FT_FILES))
# FT_OBJECTS:= $(addprefix $(OBJ_PATH)/,$(FT_OBJECTS))

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:$(LIBFT_NAME)

$(LIBFT_NAME): $(FT_OBJECTS)
	@$(AR) rcs $@ $^

clean:
	@$(RM) $(FT_OBJECTS)

fclean: clean
	@$(RM) $(LIBFT_NAME)

re: fclean all

.PHONY: all clean fclean re
