NAME := ft_ping

CC := cc

CFLAGS := -Wall -Wextra -Werror

SRCS := main.c args.c utils.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

d: CFLAGS :=
d: re

.PHONY: all clean fclean re d

# --leak-check=full --show-leak-kinds=all --track-origins=yes
