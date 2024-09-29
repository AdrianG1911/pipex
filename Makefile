NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm

SRCS		= src/pipex.c src/pathstuff.c src/utils.c src/parse_args.c \
			  src/parse_args_count.c src/parse_args_sep.c \
			  src/parse_args_wc.c src/open.c \
			  src/error.c src/init_pipex.c

BONUS_SRCS 	= 



OBJS		= $(SRCS:.c=.o)
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

all: $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	make -C libft
	$(CC) $(OBJS) $(BONUS_OBJS) -Llibft -lft -o $(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	make clean -C libft

fclean:
	$(RM) $(OBJS) $(BONUS_OBJS)
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY : all clean fclean re bonus