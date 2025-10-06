#include "RPN.hpp"

int main(int ac, char **av)
{

	if (ac != 2 || !av[1])
	{
		std::cout << "Error" << std::endl;
		return (0);
	}
	try
	{
		RPN rpn(av[1]);
		rpn.calculate();
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return (1);
	}
	return (0);
}
