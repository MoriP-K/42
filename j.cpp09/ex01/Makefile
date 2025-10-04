NAME := RPN

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRC := main.cpp RPN.cpp

OBJ := ${SRC:.o=.cpp}

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} $^ -o $@

%.o: %.cpp
	${CXX} ${CXXFLAGS} $< -c -o $@

clean:
	${RM} -r ${OBJ}

fclean: clean
	${RM} -r ${NAME}

re: fclean all

.PHONY: all clean fclean re