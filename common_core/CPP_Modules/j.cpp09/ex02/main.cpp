#include "PmergeMe.hpp"

void invalidArgument(void)
{
	std::cerr << "Error" << std::endl;
}

double getTime(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000.0 + time.tv_usec);
}

int main(int ac, char const *av[])
{
	if (ac < 2 || !av[1])
	{
		invalidArgument();
		return (1);
	}
	try
	{
		// vector
		PmergeMe pmergeme(av);
		pmergeme.initArrVec();
		std::cout << "Before: ";
		pmergeme.printArrBeforeSortingVec();
	
		double start_vec = getTime();
		pmergeme.startSortingVec();
		double end_vec = getTime();
		double time_vec = end_vec - start_vec;

		// deque
		pmergeme.initArrDeq();
	
		double start_deq = getTime();
		pmergeme.startSortingDeq();
		double end_deq = getTime();
		double time_deq = end_deq - start_deq;

		// result
		std::cout << "After : ";
		pmergeme.printArrAfterSortingDeq();

		std::cout << std::fixed << std::setprecision(0);

		std::cout << "Time to process a range of " << pmergeme.arrSizeVec()
				  << " elements with std::vector : "
				  << time_vec << " us" << std::endl;
		
		std::cout << "Time to process a range of " << pmergeme.arrSizeDeq()
				  << " elements with std::deque  : "
				  << time_deq << " us" << std::endl;

		// 
		// std::cout << "\n======= RESULT =======" << std::endl;
		// std::cout << "vector: " << pmergeme.getCountVec() << std::endl;
		// std::cout << "deque : " << pmergeme.getCountDeq() << std::endl;
		// std::cout << "\n======= AFTER =======" << std::endl;
		// std::cout << "vector: "; 
		// pmergeme.printArrAfterSortingVec();
		// std::cout << "deque : ";
		// pmergeme.printArrAfterSortingDeq();
	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 0;
}
