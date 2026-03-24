#include "RPN.hpp"

int main(int ac, char **av)
{

	if (ac != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		RPN rpn(av[1]);
		rpn.calculate();
	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return (1);
	}
	return (0);
}
