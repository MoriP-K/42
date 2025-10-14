#include "PmergeMe.hpp"

int main(int ac, char const *av[])
{
	if (ac == 1 || !av[1])
		return (1);
	try
	{
		PmergeMe pmergeme(av);

		pmergeme.printArr(pmergeme.getArr(), "\nBefore: ");
		pmergeme.printArr(pmergeme.getSorted(), "After : ");
		std::vector<int> vec = pmergeme.generateJacobsthal(10);
		pmergeme.printArr(vec, "jacob: ");
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
	return 0;
}
