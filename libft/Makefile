# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 15:49:40 by adrgutie          #+#    #+#              #
#    Updated: 2024/08/17 21:45:40 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
RM 		= rm -f
SRCS 	= ft_p_char_str.c ft_p_int_uint.c ft_p_ptr_hex.c ft_printf.c 
OBJS 	= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libftnop
	cp ./libftnop/libftnop.a $(NAME)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make fclean -C libftnop
fclean: clean
	$(RM) $(NAME)
re: fclean all
bonus: all
.PHONY : all clean fclean re