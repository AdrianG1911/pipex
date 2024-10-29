# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 16:11:57 by adrgutie          #+#    #+#              #
#    Updated: 2024/10/08 18:28:33 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -fr
OBJ_DIR		= obj

SRCS		= src/pipex.c \
			  src/pathstuff.c \
			  src/free.c \
			  src/parse_args.c \
			  src/parse_args_count.c \
			  src/parse_args_sep.c \
			  src/parse_args_wc.c \
			  src/open.c \
			  src/error.c \
			  src/init_pipex.c \
			  src/thing_to_thing.c


OBJS		= $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -g -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re