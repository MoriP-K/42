NAME := ex00

CXX := c++

CXXFLAGS := -std=c++98 -pedantic -Wall -Wextra -Werror -g

SRC := main.cpp ScalarConverter.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r