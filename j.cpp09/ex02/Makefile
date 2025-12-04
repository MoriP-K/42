NAME := PmergeMe

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

SRC := main.cpp

OBJ := ${SRC:.cpp=.o}

HEADER := PmergeMe.hpp PmergeMe.tpp

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} $^ -o $@

%.o: %.cpp ${HEADER}
	${CXX} ${CXXFLAGS} $< -c -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

rr: re
	${MAKE} clean

.PHONY: all clean fclean re rr