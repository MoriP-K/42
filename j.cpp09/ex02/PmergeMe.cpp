#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->comparePair(this->_arr);
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

void PmergeMe::comparePair(std::vector<int> bigger)
{
	std::vector<int> pending;
	size_t i = 0;
	if (bigger.size() == 1)
	{
		return ;
	}
	for (std::vector<int>::iterator it = _arr.begin(); it != _arr.end(); ++it)
	{
		if (_arr[i + 1])
		{
			if (_arr[i] < _arr[i + 1])
			{
				_main.push_back(_arr[i + 1]);
				pending.push_back(_arr[i]);
			}
			else
			{
				_main.push_back(_arr[i]);
				pending.push_back(_arr[i + 1]);
			}
		}
		else
			pending.push_back(_arr[i]);
		++it;
		i += 2;
	}
	printArr(_main, "main: ");
	printArr(pending, "pend: ");
	std::cout << "eeeeeee\n" << std::endl;
	comparePair(_main);
}

const std::vector<int> PmergeMe::getArr() const
{
	return (this->_arr);
}

void PmergeMe::printArr(std::vector<int> vec, std::string msg)
{
	std::cout << msg;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (it + 1 == vec.end())
			std::cout << *it << std::endl;
		else
			std::cout << *it << ", ";
	}
}
