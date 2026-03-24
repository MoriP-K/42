NAME := ex01

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g

SRC := main.cpp Span.cpp

OBJ := ${SRC:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} $^ -o $@

%.o: %.cpp
	${CXX} ${CXXFLAGS} $< -c -o $@

clean:
	${RM} -f ${OBJ}

fclean: clean
	${RM} -f ${NAME}

re: fclean all

.PHONY: all clean fclean re