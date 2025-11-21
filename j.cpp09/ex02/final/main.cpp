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
		std::cout << std::endl;
		// mis.printInfo(mis.getPairOrigIdx(), WHITE);
		mis.startSorting();
		// mis.printCount();
		std::cout << mis.getArr() << " ";

	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << '\n';
	}
	
	return 0;
}
