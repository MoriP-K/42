NAME := ex00

CCX := c++

CPPFLAG := -Wall -Wextra -Werror -std=c++98 -pedantic -g

SRC := main.cpp ScalarConverter.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAG) $(OBJ) -o $(NAME)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r