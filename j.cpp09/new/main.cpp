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

		std::vector<data> info;
		info = mis.initData();
		std::cout << "======== input ========" << std::endl;
		std::cout << std::endl;
		mis.printInfo(info, WHITE, false);
		mis.startSorting(info);
		mis.printCount();
		std::cout << mis.getArr() << " ";

	}
	catch(const std::exception& error)
	{
		std::cerr << error.what() << '\n';
	}
	
	return 0;
}
