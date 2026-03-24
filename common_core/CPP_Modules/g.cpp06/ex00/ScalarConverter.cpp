#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(std::string &copy)
{
	(void)copy;
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

void ScalarConverter::convert(const std::string &literal)
{
	printChar(literal);
	printInt(literal);
	printFloat(literal);
	printDouble(literal);
}

void printChar(const std::string &literal)
{
	std::cout << "char: ";

	if (literal == "nan" || literal == "nanf" ||
		literal == "inf" || literal == "+inf" || literal == "-inf" ||
		literal == "inff" || literal == "+inff" || literal == "-inff")
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (literal.length() == 1 && !isdigit(literal[0]))
	{
		char c = literal[0];
		if (33 <= c && c <= 126)
			std::cout << "'" << c << "'" << std::endl;
		else
			std::cout << "Non displayble" << std::endl;
		return ;
	}
	char *endptr;
	double d = strtod(literal.c_str(), &endptr);
	if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0'))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	long num = static_cast<long>(d);
	if (num < 0 || num > 127)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (32 <= num && num <= 126)
		std::cout << "'" << static_cast<char>(num) << "'" << std::endl;
	else
		std::cout << "Non displayble" << std::endl;
}

void printInt(const std::string &literal)
{
	std::cout << "int: ";
	if (literal == "nan" || literal == "nanf" ||
		literal == "inf" || literal == "+inf" || literal == "-inf" ||
		literal == "inff" || literal == "+inff" || literal == "-inff")
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (literal.length() == 1 && !isdigit(literal[0]))
	{
		char c = literal[0];
		if (32 <= c && c <= 126)
			std::cout << static_cast<int>(c) << std::endl;
		else
			std::cout << "impossible" << std::endl;
		return ;
	}
	char *endptr;
	double d = strtod(literal.c_str(), &endptr);
	if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0'))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (d < INT_MIN || INT_MAX < d)
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	std::cout << static_cast<int>(d) << std::endl;
}

void printFloat(const std::string &literal)
{
	std::cout << "float: ";
	if (literal == "nanf")
	{
		std::cout << "nanf" << std::endl;
		return ;
	}
	if (literal == "+inff" || literal == "inff")
	{
		std::cout << "+inff" << std::endl;
		return ;
	}
	if (literal == "-inff")
	{
		std::cout << "-inff" << std::endl;
		return ;
	}
	if (literal == "nan")
	{
		std::cout << "nanf" << std::endl;
		return ;
	}
	if (literal == "+inf" || literal == "inf")
	{
		std::cout << "+inff" << std::endl;
		return ;
	}
	if (literal == "-inf")
	{
		std::cout << "-inff" << std::endl;
		return ;
	}
	if (literal.length() == 1 && !isdigit(literal[0]))
	{
		char c = literal[0];
		if (32 <= c && c <= 126)
			std::cout << static_cast<float>(c) << ".0f" << std::endl;
		else
			std::cout << "impossible" << std::endl;
		return ;
	}
	char *endptr;
	double d = strtod(literal.c_str(), &endptr);
	if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0'))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	float f = static_cast<float>(d);
	if (f == static_cast<int>(f)) // 整数なら.0fをつける
		std::cout << f << ".0f" << std::endl;
	else
		std::cout << f << "f" << std::endl;
}

void printDouble(const std::string &literal)
{
	std::cout << "double: ";
	if (literal == "nan" || literal == "nanf")
	{
		std::cout << "nan" << std::endl;
		return ;
	}
	if (literal == "+inf" || literal == "inf" ||
		literal == "+inff" || literal == "inff")
	{
		std::cout << "+inf" << std::endl;
		return ;
	}
	if (literal == "-inf" || literal == "-inff")
	{
		std::cout << "-inf" << std::endl;
		return ;
	}
	if (literal.length() == 1 && !isdigit(literal[0]))
	{
		char c = literal[0];
		if (32 <= c && c <=126)
			std::cout << static_cast<double>(c) << ".0" << std::endl;
		else
			std::cout << "impossible" << std::endl;
		return ;
	}
	char *endptr;
	double d = strtod(literal.c_str(), &endptr);
	if (*endptr != '\0' && !(*endptr == 'f' && *(endptr + 1) == '\0'))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	if (d == static_cast<int>(d)) // 整数なら.0をつける
		std::cout << d << ".0" << std::endl;
	else
		std::cout << d << std::endl;
}
