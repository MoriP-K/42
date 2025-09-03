#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <limits>

class ScalarConverter
{
private:
	ScalarConverter();

public:
	~ScalarConverter();
	ScalarConverter(std::string &copy);
	ScalarConverter &operator=(ScalarConverter& src);

	static void convert(std::string &literal);
	static void printChar(std::string &literal);
	static void printInt(std::string &literal);
	static void printFloat(std::string &literal);
	static void printDouble(std::string &literal);
};

#endif
