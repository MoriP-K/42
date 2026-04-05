NAME := ft_ping

CC := cc

CFLAGS := -Wall -Wextra -Werror -I include

SRCDIR := src
SRCS := $(SRCDIR)/main.c $(SRCDIR)/args.c $(SRCDIR)/utils.c $(SRCDIR)/icmp.c

OBJDIR := obj
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c include/ft_ping.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

d: CFLAGS := -I include
d: re

.PHONY: all clean fclean re d

# valgrind command options
# --leak-check=full --show-leak-kinds=all --track-origins=yes
