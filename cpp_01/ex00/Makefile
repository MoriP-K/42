NAME := Brainz
CC := c++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
SRC := main.cpp newZombie.cpp randomChump.cpp Zombie.cpp
OBJDIR := ./obj
OBJ := $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/%.o:%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJ) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r