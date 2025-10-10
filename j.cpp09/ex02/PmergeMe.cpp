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
	int	num;

	for (size_t i = 1; av[i]; ++i)
	{
		num = std::atoi(av[i]);
		if (num < 0)
			return (false);
		this->_arr.push_back(num);
	}
	return (true);
}

void PmergeMe::comparePair(std::vector<int> arr)
{
	std::vector<int> main;
	std::vector<int> pending;
	if (arr.size() == 1)
	{
		return ;
	}
	// std::cout << "len: " << arr.size() << std::endl;
	static size_t i = 0;
	std::cout << "\n===== " << ++i << " =====" << std::endl;
	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		size_t distance = std::distance(it, arr.end());
		if (distance % 2 == 0 || *(it + 1))
		{
			if (*it < *(it + 1))
			{
				main.push_back(*(it + 1));
				pending.push_back(*it);
			}
			else
			{
				main.push_back(*it);
				pending.push_back(*(it + 1));
			}
			++it;
		}
		else
			pending.push_back(*it);
	}
	printArr(pending, "pend: ");
	printArr(main, "main: ");
	comparePair(main);

	std::cout << "\n----- BACK -----" << std::endl;
	printArr(pending, "pend: ");
	printArr(main, "main: ");

	for (std::vector<int>::iterator it = pending.begin(); it != pending.end(); ++it)
	{
		// func(): search for postion to insert pending into main 
	}

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
