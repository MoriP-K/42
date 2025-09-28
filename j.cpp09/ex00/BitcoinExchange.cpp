#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(char *input)
{
	this->loadDatabase();
	this->execute(input);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _dataFromCSV(copy._dataFromCSV)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream file("data.csv");

	if (!file)
		throw CouldNotOpenFileException();

	std::string line;
	size_t comma_pos = 0;

	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw CouldNotOpenFileException();
	while (std::getline(file, line))
	{
		comma_pos = line.find(",");
		if (comma_pos != std::string::npos)
		{
			std::string date_part = trim(line.substr(0, comma_pos));
			int value_part = atoi(trim(line.substr(comma_pos + 1)).c_str());
			this->_dataFromCSV[date_part] = value_part;
		}
	}
}

void BitcoinExchange::execute(char *input)
{
	std::ifstream file(input);
	std::string line;
	size_t pipe_pos;
	size_t i = 0;

	while (std::getline(file, line))
	{
		if (i == 0 && line == "date | value")
		{
			i++;
			continue;
		}
		pipe_pos = line.find("|");
		if (pipe_pos == std::string::npos)
			throw BadInputException(line);
		std::string date_part = trim(line.substr(0, pipe_pos));
		int value_part = atoi(trim(line.substr(pipe_pos + 1)).c_str());

		std::cout << "date : " << date_part << std::endl;
		std::cout << "value: " << value_part << std::endl;
	}
}

std::string trim(const std::string &str)
{
	std::string::const_iterator start = str.begin();
	std::string::const_iterator end = str.end();

	while (start != end && isspace(*start))
		++start;
	while (end != start && isspace(*(end - 1)))
		--end;
	return (std::string(start, end));
}
