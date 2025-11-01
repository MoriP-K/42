#include "PmergeMe.hpp"

int main(int ac, char const *av[])
{
	if (ac < 2)
	{
		invalidArgument();
		return (1);
	}
	try
	{
		PmergeMe mis(av);

	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << '\n';
	}
	
	return 0;
}
