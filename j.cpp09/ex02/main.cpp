#include "PmergeMe.hpp"

double getTime(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

int main(int ac, char const *av[])
{
	if (ac < 2)
	{
		std::cout << "Error" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe pmergeme(av);

		pmergeme.printArr(pmergeme.getArr(), "Before: ");

		double startVec = getTime();
		pmergeme.MIS(pmergeme.getArr());
		// pmergeme.mergeInsertionSort();
		double endVec = getTime();
		double timeVec = endVec - startVec;

		pmergeme.printCount();
		pmergeme.printArr(pmergeme.getSorted(), "After : ");

		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << pmergeme.arrSize()
				<< " elements with std::vector : " << timeVec << " us" << std::endl;
		std::cout << "Time to process a range of " << pmergeme.arrSize()
				<< " elements with std::deque : " << "timeDeq" << " us" << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
	return 0;
}
