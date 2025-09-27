#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <exception>
#include <fstream>

class BitcoinExchange
{
private:
	std::map<std::string, int> _data;
	int _price;

public:
	BitcoinExchange();
	BitcoinExchange(char *inputFIle);
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange &operator=(const BitcoinExchange &src);
	~BitcoinExchange();

	void readFile(char *inputFile);

	class CouldNotOpenFileException: public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("could not open file.");
		}
	};

	class NotPositiveNumberException: public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("not a positive number.");
		}
	};

	class BadInputException: public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("bad input => ");
		}
	};

	class TooLargeNumberException: public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("too large a number.");
		}
	};
};

#endif
