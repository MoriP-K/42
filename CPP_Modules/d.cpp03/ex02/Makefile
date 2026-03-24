NAME := Serena

CXX := c++

CPPFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR := ./src
SRC := main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

OBJDIR := ./obj
OBJ := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

HEADDIR := ./inc
HEADER := ClapTrap.hpp ScavTrap.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CPPFLAGS) -I$(HEADDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -rf $(OBJDIR)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r