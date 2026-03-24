#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <climits>
#include <cstdlib>
#include <cctype>

class ScalarConverter
{
private:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(std::string &copy);
	ScalarConverter &operator=(ScalarConverter& src);

	public:
	static void convert(const std::string &literal);
};

void printChar(const std::string &literal);
void printInt(const std::string &literal);
void printFloat(const std::string &literal);
void printDouble(const std::string &literal);
#endif
