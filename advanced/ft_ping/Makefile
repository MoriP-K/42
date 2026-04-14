NAME := ft_ping

CC := cc

CFLAGS := -Wall -Wextra -Werror -I include
LDFLAGS := -lm

# SRCDIR := src
SRCS := main.c utils.c print.c usage.c icmp.c set.c

# OBJDIR := obj
OBJS := $(SRCS:.c=.o)

HDR := ft_ping.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

d: CFLAGS += -g
d: re

.PHONY: all clean fclean re d

# valgrind command options
# --leak-check=full --show-leak-kinds=all --track-origins=yes
