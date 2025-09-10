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
};

void convert(std::string &literal);
void printChar(std::string &literal);
void printInt(std::string &literal);
void printFloat(std::string &literal);
void printDouble(std::string &literal);

#endif
