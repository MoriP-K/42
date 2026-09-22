NAME := ft_traceroute

CC := cc

CFLAGS := -Wall -Werror -Wextra

SRCS := main.c icmp.c utils.c print.c print2.c

OBJS := $(SRCS:.c=.o)

HDR := ft_traceroute.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re