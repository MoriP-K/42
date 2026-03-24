NAME := ex00

CXX := c++

CXXFLAGS := -std=c++98 -pedantic -Wextra -Wall -Werror

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) -r $(NAME)

re: fclean all

.PHONY: all clean fclean re