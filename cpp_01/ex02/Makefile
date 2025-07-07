NAME := HiThisIsBrain

CXX := C++

CFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRC := main.cpp

# OBJDIR := ./obj

OBJ := $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $^ -o $@

# $(OBJDIR)/%.o:%.cpp | $(OBJDIR)
# 	$(CXX) $(CFLAGS) $< -c -o $@

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

r:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re r
