#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(char *inputFile)
{
	this->readFile(inputFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _data(copy._data), _price(copy._price)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->_data = src._data;
		this->_price = src._price;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::readFile(char *inputFile)
{
	std::ifstream file(inputFile);
	std::string line;
	int pipe_pos;

	if (!file)
		throw CouldNotOpenFileException();

	size_t i = 0;
	while (std::getline(file, line))
	{
		if (i == 0 && line == "date | value")
		{
			i++;
			continue;
		}
		pipe_pos = line.find("|");
		std::cout << line << std::endl;
	}
}