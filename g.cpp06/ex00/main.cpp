#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	
	if (ac != 2 || !av)
		return 1;

	std::string literal(av[1]);

	ScalarConverter::convert(literal);
}