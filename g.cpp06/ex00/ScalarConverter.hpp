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
	static void printChar(const std::string &literal);
	static void printInt(const std::string &literal);
	static void printFloat(const std::string &literal);
	static void printDouble(const std::string &literal);
public:
	static void convert(const std::string &literal);
};

#endif
