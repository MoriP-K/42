NAME := minishell
CC := cc
CPPFLAGS := -I./includes
CFLAGS := -Wall -Wextra -Werror
SRC := main.c
OBJDIR := ./obj
OBJ := $(SRC:%.c=$(OBJDIR)/%.o)
RLFLAGS := -lreadline

vpath %.c ./src

ifeq ($(DEBUG), true)
	CFLAGS += -g -O0 -fsanitize=address
	CFLAGS := -Wall -Wextra
endif

all: $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(RLFLAGS)

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

d: clean
	$(MAKE) DEBUG=true

.PHONY: all clean fclean re rr d 