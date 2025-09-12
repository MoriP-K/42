NAME := ex00

CPP := c++

CPPFLAGS := -std=c++98 -pedantic -Wextra -Wall -Werror

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) -r $(NAME)

re: fclean all

.PHONY: all clean fclean re