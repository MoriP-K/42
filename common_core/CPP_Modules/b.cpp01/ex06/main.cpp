#include "Harl.hpp"

int main(int ac, char const *av[])
{
	std::string level;
	Harl harl;

	if (ac != 2)
	{
		std::cerr << "Invalid Argument." << std::endl;
		return (1);
	}
	level = av[1];
	harl.complain(level);
	return (0);
}
