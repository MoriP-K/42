NAME := ex01

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g

SRC := main.cpp Serializer.cpp

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