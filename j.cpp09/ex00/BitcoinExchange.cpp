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
		{
			this->errorBadInput(line);
			continue;
		}

		std::string date_part = trim(line.substr(0, pipe_pos));

		if (!this->isValidDate(date_part))
			this->errorBadInput(date_part);
		int value_part = atoi(trim(line.substr(pipe_pos + 1)).c_str());
		if (!this->isValidValue(value_part))
			this->errorNotPositiveNumber();
		// std::cout << "date : " << date_part << std::endl;
		// std::cout << "value: " << value_part << std::endl;
	}
}

bool BitcoinExchange::isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		if (!isdigit(date[i]))
			return (false);
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	std::cout << year << "-" << month << "-" << day << std::endl;
	
	if (year < 2009 || 2025 < year)
		return (false);
	if (month < 1 || 12 < month)
		return (false);
	if (day < 1 || 31 < day)
		return (false);
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		daysInMonth[1] = 29;
	if (day > daysInMonth[month - 1])
		return (false);
	return (true);
}

bool BitcoinExchange::isValidValue(const int &value)
{
	if (value < 0 || 1000 < value)
		return (false);
	return (true);
}

void BitcoinExchange::errorBadInput(const std::string &line)
{
	std::cout << "Error: bad input => " << line << std::endl;
}

void BitcoinExchange::errorTooLargeNumber(void)
{
	std::cout << "Error: too large a number." << std::endl;
}

void BitcoinExchange::errorNotPositiveNumber(void)
{
	std::cout << "Error: not a positive number." << std::endl;
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
