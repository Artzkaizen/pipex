# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chuezeri <chuezeri@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 12:13:36 by chuezeri          #+#    #+#              #
#    Updated: 2025/06/02 16:39:29 by chuezeri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME		= pipex
CC			= cc

SRC_DIR		:= src
OBJ_DIR		= objs
INCLUDE_DIR	= includes

CFLAGS		= -Wall -Wextra -Werror -I$(INCLUDE_DIR)

SRCS		= main.c pipex.c utils.c path.c ft_libft_fns.c ft_split.c get_next_line.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM			= rm -f

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

# Full clean (remove object files and static library)
fclean: clean
	$(RM) $(NAME)

# Rebuild the project
re: fclean all


.PHONY: all clean fclean re