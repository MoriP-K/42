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

void PmergeMe::comparePair(std::vector<int> main)
{
	size_t	i;

	std::vector<int> pending;
	i = 0;
	if (main.size() == 1)
	{
		return ;
	}
	std::cout << "len: " << main.size() << std::endl;

	for (std::vector<int>::iterator it = main.begin(); it != main.end(); ++it)
	{
		size_t distance = std::distance(it, main.end());
		std::cout << "dist: " << distance << std::endl;
		if (distance < 0)
			return ;
		if (distance % 2 == 0 || *(it + 1))
		{
			if (*it < *(it + 1))
			{
				_main.push_back(*(it + 1));
				pending.push_back(*it);
			}
			else
			{
				_main.push_back(*it);
				pending.push_back(*(it + 1));
			}
			// ++it;
			it += 2;
		}
		else
		{
			pending.push_back(*it);
			++it;
		}

	}
	// if (i == 10)
	// {
	// 	std::cout << "i = 10;" << std::endl;
	// 	return ;
	// }
	printArr(_main, "main: ");
	printArr(pending, "pend: ");
	// std::cout << "eeeeeee\n" << std::endl;
	// comparePair(_main);
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
