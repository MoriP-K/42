#include "PmergeMeVector.hpp"
#include "PmergeMeDeque.hpp"

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
		PmergeMeVector pmVector(av);
		pmVector.initArr();
		std::cout << "Before: ";
		pmVector.printArrBeforeSorting();
	
		double start_vec = getTime();
		pmVector.startSorting();
		double end_vec = getTime();
		double time_vec = end_vec - start_vec;

		// deque
		PmergeMeDeque pmDeque(av);
		pmDeque.initArr();
	
		double start_deq = getTime();
		pmDeque.startSorting();
		double end_deq = getTime();
		double time_deq = end_deq - start_deq;

		// result
		std::cout << "After : ";
		pmVector.printArrAfterSorting();

		std::cout << std::fixed << std::setprecision(0);

		std::cout << "Time to process a range of " << pmVector.arrSize()
				  << " elements with std::vector : "
				  << time_vec << " us" << std::endl;
		
		std::cout << "Time to process a range of " << pmDeque.arrSize()
				  << " elements with std::deque  : "
				  << time_deq << " us" << std::endl;

		// 
		// std::cout << "\n======= RESULT =======" << std::endl;
		// std::cout << "vector: " << pmVector.getCount() << std::endl;
		// std::cout << "deque : " << pmDeque.getCount() << std::endl;
		// std::cout << "\n======= AFTER =======" << std::endl;
		// std::cout << "vector: "; 
		// pmVector.printArrAfterSorting();
		// std::cout << "deque : ";
		// pmDeque.printArrAfterSorting();
	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
	}
	return 0;
}
