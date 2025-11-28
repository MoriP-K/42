#include "./PmergeMe.hpp"

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

		mis.initArr();
		std::cout << "======== input ========" << std::endl;
		for (size_t i = 1; av[i]; ++i)
			std::cout << av[i] << " ";
		std::cout << "\n=======================" << std::endl;
		std::cout << "() is value, [] is index.\n" << std::endl;
		// mis.printInfo(mis.getPairOrigIdx(), WHITE);
		mis.startSorting();
		std::cout << "\n======= RESULT =======" << std::endl;
		mis.printCount();
		// std::cout << "------- BEFORE -------" << std::endl;
		// mis.printArrBeforeSorting();
		std::cout << "------- AFTER -------" << std::endl;
		mis.printArrAfterSorting();

	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << '\n';
	}
	
	return 0;
}
