#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
	}
	return (*this);
}

bool PmergeMe::isValidArgs(const char **av)
{
	for (size_t i = 1; av[i]; ++i)
	{
		int num = std::atoi(av[i]);
		if (num < 0)
			return (false);
		this->_arr.push_back(num);
	}
	return (true);
}

void PmergeMe::printArr()
{
	for (std::vector<int>::iterator it = this->_arr.begin(); it != this->_arr.end(); ++it)
	{
		std::cout << *it << ", ";
	}
}
