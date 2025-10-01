#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <exception>
# include <fstream>
# include <iostream>
# include <map>

class BitcoinExchange
{
private:
	std::map<std::string, double> _dataFromCSV;
	std::ifstream _inputFile;

public:
	BitcoinExchange(char *input);
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange &operator=(const BitcoinExchange &src);
	~BitcoinExchange();

	void loadDatabase();
	void execute(char *input);
	void errorBadInput(const std::string &line);
	void errorTooLargeNumber(void);
	void errorNotPositiveNumber(void);
	bool isValidDate(const std::string &date);

	class CouldNotOpenFileException : public std::exception
	{
		public:
		virtual const char *what() const throw()
		{
			return ("Error: could not open file.");
		}
	};

	class NotPositiveNumberException : public std::exception
	{
		public:
		virtual const char *what() const throw()
		{
			return ("Error: not a positive number.");
		}
	};

	class BadInputException : public std::exception
	{
		private:
		std::string _errMsg;

		public:
		BadInputException(const std::string &line) : _errMsg("Error: bad input => " + line)
		{
		}

		virtual const char *what() const throw()
		{
			return (this->_errMsg.c_str());
		}
	};

	class TooLargeNumberException : public std::exception
	{
		public:
		virtual const char *what() const throw()
		{
			return ("Error: too large a number.");
		}
	};

	class InvalidFormatException : public std::exception
	{
		public:
		virtual const char *what() const throw()
		{
			return ("Error: invalid format.");
		}
	};
};

std::string trim(const std::string &str);

#endif
