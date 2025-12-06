#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(char *input)
{
	this->loadDatabase();
	this->execute(input);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy): _data_from_CSV(copy._data_from_CSV)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->_data_from_CSV = src._data_from_CSV;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::calculateAndDisplay(const std::string &date, double value)
{
	try
	{
		double rate = this->getPrice(date);
		double result = value * rate;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	
}


double BitcoinExchange::getPrice(const std::string &date)
{
	std::map<std::string, double>::iterator it = this->_data_from_CSV.find(date);
	if (it != this->_data_from_CSV.end())
		return (it->second);
	std::map<std::string, double>::iterator lower = this->_data_from_CSV.lower_bound(date);
	if (lower == this->_data_from_CSV.begin())
		throw std::runtime_error("No price data available for this date");
	--lower;
	return (lower->second);
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream file("data.csv");

	if (!file)
		throw CouldNotOpenFileException();

	std::string line;
	size_t comma_pos = 0;

	while (std::getline(file, line))
	{
		if (line == "date,exchange_rate")
			continue;
		comma_pos = line.find(",");
		if (comma_pos != std::string::npos)
		{
			std::string date = trim(line.substr(0, comma_pos));
			char **endptr = NULL;
			double rate = std::strtod(trim(line.substr(comma_pos + 1)).c_str(), endptr);
			this->_data_from_CSV[date] = rate;
			// std::cout << "Date: " << date << ", Rate: " << value_part << std::endl;
		}
	}
}

void BitcoinExchange::execute(char *input)
{
	std::ifstream file(input);
	std::string line;
	size_t pipe_pos;
	size_t i = 0;

	if (!file)
		throw CouldNotOpenFileException();

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
		{
			this->errorBadInput(date_part);
			continue;
		}
		char **endptr = NULL;
		double value_part = std::strtod(trim(line.substr(pipe_pos + 1)).c_str(), endptr);
		if (!this->isPositiveValue(value_part))
		{
			this->errorNotPositiveNumber();
			continue;
		}
		else if (!this->isInRange(value_part))
		{
			this->errorTooLargeNumber();
			continue;
		}
		else
			this->calculateAndDisplay(date_part, value_part);
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
	
	if (year < 2009 || 2025 < year)
		return (false);
	if (month < 1 || 12 < month)
		return (false);
	if (day < 1 || 31 < day)
		return (false);
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		days_in_month[1] = 29;
	if (day > days_in_month[month - 1])
		return (false);
	return (true);
}

bool BitcoinExchange::isPositiveValue(const double &value)
{
	return (value >= 0);
}
bool BitcoinExchange::isInRange(const double &value)
{
	return (1000 >= value);
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
