NAME := animal

CXX := c++

CPPFLAGS := -Wextra -Werror -Wall

SRC := main.cpp Animal.cpp

OBJ := ${SRC:.cpp=.o}

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

.PHONY: all clean fclean re