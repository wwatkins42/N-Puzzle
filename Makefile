# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tglaudel <tglaudel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 16:02:35 by tglaudel          #+#    #+#              #
#    Updated: 2017/02/08 09:16:02 by wwatkins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_PATH = obj/

SRCS_PATH = srcs/

SRCS_NAME = main.c \
		   astar.c \
		   list.c \
		   parse.c \
		   utils.c \
		   heuristic.c \

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJ = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

NAME = npuzzle

CC = gcc

LIBFT = libft/libft.a

INCLUDES = ./libft/include/

CFLAGS = -Wall -Werror -Wextra -O3

all: omkdir $(NAME)

omkdir:
	mkdir -p $(OBJS_PATH)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MINILIB) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDES) -I includes

$(LIBFT):
	make -C libft

clean:
	rm -rf $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all re clean fclean
