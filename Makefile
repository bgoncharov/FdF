# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bogoncha <bogoncha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 17:15:00 by bogoncha          #+#    #+#              #
#    Updated: 2019/06/27 17:35:15 by bogoncha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC_PATH = ./
OBJ_PATH = ./
INC = -I /usr/local/include
LDFLAGS = -L ./minilibx -L ./libft
LDLIBS = -lmlx -framework OpenGL -framework AppKit -lft
CFLAGS = -Wall -Wextra -Werror 
CC = gcc
SRC = main.c \
	parser.c \
	drawing.c \
	keyboard.c \
	tools.c

all: $(NAME)

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	@echo "\033[32m>>\033[0m \033[33mStarting library & $(NAME)\033[32m compilation\033[0m \033[0m"
	@make -C libft
	@make -C minilibx
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "\033[32m>> $(NAME) correctly created ... OK\033[0m"

%.o: %.c fdf.h
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	@echo "\033[32mObjects \033[31mremoved\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "\033[32m$(NAME) \033[31mremoved\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re