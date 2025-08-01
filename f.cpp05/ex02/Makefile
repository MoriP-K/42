NAME := Bereaucrat

CXX := c++

CPPFLAGS := -Wextra -Werror -Wall -std=c++98 -pedantic -g

SRC_DIR := ./src
SRC := main.cpp Bureaucrat.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreatioinForm.cpp

OBJ_DIR := ./obj
OBJ := ${addprefix ${OBJ_DIR}/, ${SRC:.cpp=.o}}

HEADER_DIR := ./inc
HEADER := Bureaucrat.hpp AForm.hpp p PresidentialPardonForm.hpp RobotomyRequestForm.hpp ShrubberyCreatioinForm.hpp

all: ${NAME}

${NAME}: ${OBJ}
	${CXX} ${CPPFLAGS} ${OBJ} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp | ${OBJ_DIR}
	${CXX} ${CPPFLAGS} -I${HEADER_DIR} -c $< -o $@

${OBJ_DIR}:
	mkadir -p ${OBJ_DIR}

clean:
	${RM} -f ${OBJ}

fclean: clean
	${RM} -f ${NAME}

re: fclean all

r:
	${MAKE} re
	${MAKE} clean

.PHONY: all clean fclean re r