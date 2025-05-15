NAME := philo

CC := cc

CPPFLAGS := -I./includes

CFLAGS := -Wall -Wextra -Werror

SRC := main.c utils.c philo_list.c ft_atoi.c free.c \
		philo_lifecycle.c init.c monitor.c mutex.c threads.c \

OBJDIR := ./obj

OBJ := $(SRC:%.c=$(OBJDIR)/%.o)

vpath %.c ./src:

ifeq ($(DEBUG), true)
	CFLAGS += -g3
endif

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

d: clean
	$(MAKE) DEBUG=true

.PHONY: all clean fclean re rr