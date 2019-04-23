# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arudyi <arudyi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/15 15:00:28 by arudyi            #+#    #+#              #
#    Updated: 2019/04/23 12:19:15 by arudyi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INCLUDE_DIR = ./include/
LIB_DIR = ./lib/
SRC = main.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR := $(LIB_DIR)libft/
LIBFT_INC := $(LIBFT_DIR)includes/
LIBFT_FLAGS := -lft -L $(LIBFT_DIR)
CC_FLAGS = -g
LINK_FLAGS := $(LIBFT_FLAGS)
HEADER_FLAGS := -I $(INCLUDE_DIR) \
				-I $(LIBFT_INC) \
				-I./frameworks/SDL2.framework/Headers \
                -I./frameworks/SDL2_image.framework/Headers \
                -I./frameworks/SDL2_ttf.framework/Headers \
                -I./frameworks/SDL2_mixer.framework/Headers \
                -F./frameworks
CC := gcc
FRAMEWORK = -F./frameworks \
            -rpath ./frameworks \
            -framework AppKit -framework OpenGL \
            -framework SDL2 -framework SDL2_image \
            -framework SDL2_mixer -framework SDL2_ttf \

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FRAMEWORK) $(LINK_FLAGS)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@ $(HEADER_FLAGS)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

vpath %.c $(SRC_DIR)