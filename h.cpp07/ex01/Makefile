NAME := ex01

CXX := c++

CPPFLAGS := -Wextra -Wall -Werror -std=c++98 -pedantic

SRC := main.cpp

OBJ := ${SRC:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CPP} ${CPPFLAGS} ${OBJ} -o ${NAME}

%.o: %.cpp
	${CPP} ${CPPFLAGS} -c $< -o $@

clean:
	${RM} -f ${OBJ}

fclean: clean
	${RM} -f ${NAME}

re: fclean all

.PHONY: all clean fclean re