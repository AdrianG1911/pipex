# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrgutie <adrgutie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 17:26:17 by adrgutie          #+#    #+#              #
#    Updated: 2024/08/17 20:32:21 by adrgutie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftnop.a
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror
RM 		= rm -f
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
ft_memcpy.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strncmp.c ft_memcmp.c ft_strlcat.c ft_strdup.c \
ft_strchr.c ft_strrchr.c ft_memchr.c ft_strnstr.c ft_atoi.c ft_bzero.c ft_memmove.c ft_calloc.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS 		+= $(BONUS_SRC)
OBJS 		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)
OBJS		+= $(BONUS_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) 
fclean: clean
	$(RM) $(NAME)
re: fclean all
bonus: all
.PHONY : all clean fclean re