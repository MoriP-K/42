NAME := ex01

CXX := c++

CPPFLAGS := -Wextra -Werror -Wall -std=c++98 -pedantic -g

SRC := main.cpp Bureaucrat.cpp Form.cpp

OBJ := ${SRC:.cpp=.o}

HEADER := Bureaucrat.hpp Form.hpp

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CPPFLAGS} ${OBJ} -o ${NAME}

clean:
	${RM} -f ${OBJ}

fclean: clean
	${RM} -f ${NAME}

re: fclean all

r:
	${MAKE} re
	${MAKE} clean

.PHONY: all clean fclean re r