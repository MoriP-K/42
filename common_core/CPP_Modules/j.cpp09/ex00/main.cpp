#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "usage: ./btc <file>" << std::endl;;
		return (1);
	}

	try
	{
		
		BitcoinExchange bc(av[1]);
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return (1);
	}
	return (0);
}
