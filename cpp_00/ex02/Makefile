NAME := TheJobOfYourDream
CC := c++
CFLAGS := -Wall -Wextra -Werror
SRC := tests.cpp
OBJDIR := ./obj
OBJ := $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

$(OBJDIR)/%.o:%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -c -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) -r $(OBJ) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

rr:
	$(MAKE) re
	$(MAKE) clean

.PHONY: all clean fclean re rr