NAME := animal

CXX := c++

CPPFLAGS := -Wextra -Werror -Wall -std=c++98 -pedantic

SRCDIR := ./src
SRC := main.cpp Animal.cpp Dog.cpp Cat.cpp WrongAnimal.cpp WrongCat.cpp
		Brain.cpp

OBJDIR := ./obj
OBJ := ${addprefix ${OBJDIR}/, ${SRC:.cpp=.o}}

HEADDIR := ./inc
HEADER := Animal.hpp Dog.hpp Cat.hpp WrongAnimal.hpp WrongCat.hpp
		Brain.hpp

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CPPFLAGS} ${OBJ} -o ${NAME}

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CPPFLAGS) -I$(HEADDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	${RM} -rf ${OBJDIR}

fclean: clean
	${RM} -f ${NAME}

re: fclean all

r:
	${MAKE} re
	${MAKE} clean

.PHONY: all clean fclean re r