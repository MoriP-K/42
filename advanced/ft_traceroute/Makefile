NAME := ft_traceroute

CC := cc

CFLAGS := -Wall -Werror -Wextra

SRCS := main.c utils.c

OBJS := $(SRCS:.c=.o)

HDR := ft_traceroute.h

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re