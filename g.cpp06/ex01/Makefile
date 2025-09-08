NAME := ex01

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g

SRC := main.cpp Serialize.cpp

OBJ := $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re