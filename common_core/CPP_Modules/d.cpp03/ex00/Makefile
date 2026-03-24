NAME := Aaaaand...OPEN!

CXX := c++

CPPFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRC := main.cpp ClapTrap.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r