NAME := MySed

CXX := c++

CPPFLAGS := -Wextra -Wall -Werror -std=c++98 -pedantic

SRC := main.cpp 

OBJ := $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r
