CC = cc

CFLAGS = -Wall -Werror -Wextra -I. -Ilibft

SRCS = push_swap.c check_arg.c commands_1.c commands_2.c commands_3.c \
		exec_cmds.c func_cmds.c init.c search_limit.c sort_by_chunky.c \
		sort_normal.c start_sort.c validation.c

OBJS = $(SRCS:.c=.o)

NAME = push_swap

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re