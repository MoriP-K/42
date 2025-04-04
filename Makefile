NAME := philo

CC := cc

CPPFLAGS := -I./includes

CFLAGS := -Wall -Wextra -Werror

SRC := main.c

OBJDIR := ./obj

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

vpath %.c ./src:

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/%.o:%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $< -c -o $@ $(CPPFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(warning obj=$(OBJDIR))

clean:
	$(RM) -r $(OBJ) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

rr:
	$(MAKE) re && $(MAKE) clean

.PHONY: all clean fclean re rr