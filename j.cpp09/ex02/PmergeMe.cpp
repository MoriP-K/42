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
		num = std::atol(av[i]);
		if (num < 0 || __INT_MAX__ < num)
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
		_sorted.push_back(arr[0]);
		return ;
	}

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
				_pair[*it] = *(it + 1);
			}
			else
			{
				main.push_back(*it);
				pending.push_back(*(it + 1));
				_pair[*(it + 1)] = *it;
			}
			++it;
		}
		else
			pending.push_back(*it);
	}
	printArr(pending, "pend: ");
	printArr(main, "main: ");
	comparePair(main);

	std::cout << "\n----- BACK " << i-- << " -----" << std::endl;
	printArr(pending, "pend: ");
	printArr(_sorted, "sort: ");

	for (std::vector<int>::iterator it = pending.begin(); it != pending.end(); ++it)
	{
		int pos = binarySearch(*it);
		if (pos != -1)
			_sorted.insert(_sorted.begin() + pos, *it);
	}
}

int PmergeMe::binarySearch(int key)
{
	int ng = -1;
	int ok = (int)_sorted.size();

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOK(mid, key))
			ok = mid;
		else
			ng = ok;
	}
	return (ok);
}

bool PmergeMe::isOK(int index, int key)
{
	if (_sorted[index] >= key)
		return (true);
	return (false);
}

const std::vector<int> PmergeMe::getArr() const
{
	return (this->_arr);
}

const std::vector<int> PmergeMe::getSorted() const
{
	return (this->_sorted);
}

std::vector<int> PmergeMe::generateJacobsthal(size_t size)
{
	std::vector<int> vec;

	for (size_t i = 0; i < size; ++i)
	{
		if (i == 0)
			vec.push_back(0);
		else if (i == 1)
			vec.push_back(1);
		else
			vec.push_back(vec[i - 2] * 2 + vec[i - 1]);
	}
	return (vec);
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

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		out << vec[i] << ", ";
	return (out);
}
