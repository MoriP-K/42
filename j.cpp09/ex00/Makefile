NAME := btc

CXX := c++

CXXFLAGS := -Wall -Wextra -Werror

SRC := main.cpp BitcoinExchange.cpp

OBJ := ${SRC:.cpp=.o}

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} $^ -o ${NAME}

%.o: %.cpp
	${CXX} ${CXXFLAGS} $< -c -o $@

clean:
	${RM} -r ${OBJ}

fclean: clean
	${RM} -r ${NAME}

re: fclean all

.PHONY: all clean fclean re