CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I.

NAME = libftprintf.a

SRCS = ft_printf.c ft_putchr.c ft_puthex_address.c ft_puthex_lower.c ft_puthex_upper.c\
		ft_putnbr_unsigned.c ft_putnbr.c ft_putstr.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re