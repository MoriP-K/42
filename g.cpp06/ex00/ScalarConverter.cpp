#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(std::string &copy)
{

}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter &ScalarConverter::operator=(ScalarConverter &src)
{
	if (this != &src)
	{

	}
	return (*this);
}

void ScalarConverter::convert(std::string &literal)
{
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}

void ScalarConverter::printChar(std::string &literal)
{
	char c = stoi(literal);

	std::cout << "char: ";
	if (0 <= c && c <= 127)
	{
		if (33 <= c && c <= 126)
		{
			std::cout << "\'" << c << "\'" << std::endl;
			return ;
		}
		else
		{
			std::cout << "Non displayble" << std::endl;
			return ;
		}
	}
	else
		std::cout << "impossible" << std::endl;
}

void ScalarConverter::printInt(std::string &literal)
{
	long num = stol(literal);

	std::cout << "int: ";
	if (num < INT32_MIN || INT32_MAX < num)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	std::cout << num << std::endl;
}

void ScalarConverter::printFloat(std::string &literal)
{
	std::cout << "float: " << literal << std::endl;
}

void ScalarConverter::printDouble(std::string &literal)
{
	std::cout << "double: " << literal << std::endl;
}
