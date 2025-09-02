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
	if (literal.length() == 1 && 33 <= literal[0] && literal[0] <= 126)
	{
		std::cout << "char: " << literal.c_str() << std::endl;
		return ;
	}
	else if (literal[0] == '\'')
	{
		if (33 <= literal[1] && literal[1] <= 126)
		{
			if (literal[2] == '\'' && literal.length() == 3)
			{
				std::cout << "char: " << literal[1] << std::endl;
			}
			return ;
		}
	}
	else
		std::cout << "Non displayble" << std::endl;
}

void ScalarConverter::printInt(std::string &literal)
{
	std::string  = literal.stoi();
	std::cout << "int: " << num << std::endl;
}

void ScalarConverter::printFloat(std::string &literal)
{
	std::cout << "float: " << literal << std::endl;
}

void ScalarConverter::printDouble(std::string &literal)
{
	std::cout << "double: " << literal << std::endl;
}