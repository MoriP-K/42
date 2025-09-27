#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	// if (ac != 2 || !av[1])
	// 	std::cout << "Error: could not open file." << std::endl;
	// std::cout << av[1] << std::endl;

	try
	{
		if (ac != 2)
			throw BitcoinExchange::CouldNotOpenFileException();

		BitcoinExchange bc(av[1]);
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	return (0);
}
