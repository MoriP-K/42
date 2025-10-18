#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->dividePendingIntoMain(this->_arr);
	this->recursiveSort(this->_main);
	this->mergePendingToMain();
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
static size_t i = 0;

void PmergeMe::dividePendingIntoMain(std::vector<int> arr)
{
	// std::vector<int> main;
	// std::vector<int> pending;

	std::cout << "\n===== " << ++i << " =====" << std::endl;

	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		size_t distance = std::distance(it, arr.end());
		std::vector<int>::iterator next_it = it;
		++next_it;
		if (distance % 2 == 0 || next_it != arr.end())
		{
			if (*it < *(it + 1))
			{
				this->_main.push_back(*(it + 1));
				this->_pending.push_back(*it);
				this->_pendingToMain[*it] = *(it + 1);
			}
			else
			{
				this->_main.push_back(*it);
				this->_pending.push_back(*(it + 1));
				this->_pendingToMain[*(it + 1)] = *it;
			}
			++it;
		}
		else
			this->_pending.push_back(*it);
	}
	printArr(this->_main, "main: ");
	printArr(this->_pending, "pend: ");
}

void PmergeMe::recursiveSort(std::vector<int> arr)
{
	std::vector<int> main;
	std::vector<int> pending;

	if (arr.size() == 1)
	{
		_sorted.push_back(arr[0]);
		return ;
	}

	// static size_t i = 0;
	std::cout << "\n===== " << ++i << " =====" << std::endl;

	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		size_t distance = std::distance(it, arr.end());
		std::vector<int>::iterator next_it = it;
		++next_it;
		if (distance % 2 == 0 || next_it != arr.end())
		{
			if (*it < *(it + 1))
			{
				main.push_back(*(it + 1));
				pending.push_back(*it);
				_pendingToMain[*it] = *(it + 1);
			}
			else
			{
				main.push_back(*it);
				pending.push_back(*(it + 1));
				_pendingToMain[*(it + 1)] = *it;
			}
			++it;
		}
		else
			pending.push_back(*it);
	}
	printArr(pending, "pend: ");
	printArr(main, "main: ");
	recursiveSort(main);

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

void PmergeMe::mergePendingToMain()
{
	size_t len = this->_pending.size();
	if (len < 1)
		return ;
	std::vector<int> jacob = this->generateJacobsthal(len);
    this->createInsertionOrder(jacob);
	for (std::vector<int>::iterator it = _pending.begin(); it != _pending.end(); ++it)
	{
		this->findPendingPair();
		int pos = binarySearch(*it);
		if (pos != -1)
			_sorted.insert(_sorted.begin() + pos, *it);
	}
}

std::vector<int> PmergeMe::generateJacobsthal(int size)
{
	std::vector<int> vec;

	int i = 0;
	while (1)
	{
		if (i == 0)
			vec.push_back(0);
		else if (i == 1)
			vec.push_back(1);
		else
		{
			if (vec[i - 2] * 2 + vec[i - 1] > size)
				break;
			else
				vec.push_back(vec[i - 2] * 2 + vec[i - 1]);
		}
		i++;
	}
	vec.erase(vec.begin(), vec.begin() + 2);
	printArr(vec, "\njacob: ");
	std::cout << std::endl;
	return (vec);
}

void PmergeMe::createInsertionOrder(std::vector<int> jacob)
{
	int k = 0;

	this->_order.push_back(0);
	size_t pendingLen = this->_pending.size();
	// std::cout << "\npending len: " << pendingLen << std::endl;
	size_t jacobSize = jacob.size();
	size_t jacobMax = jacob[jacobSize - 1];
    for (size_t i = jacob.size(); 0 < i; --i)
    {
		int n = i - 1;
        int bigger = jacob[n];
        int smaller = jacob[n - 1] + 1;

		// std::cout << "bigger : " << bigger << std::endl;
		// std::cout << "smaller: " << smaller << std::endl;
		std::cout << std::endl;
        while (smaller <= bigger)
        {
            this->_order.push_back(bigger);
			std::cout << "order[" << k++ << "]: " << bigger << std::endl;
            bigger--;
        }
		std::cout << std::endl;
    }
	std::cout << "jacob max: " << jacobMax << std::endl;
	std::cout << "pending len: " << pendingLen << std::endl;
	while (pendingLen > jacobMax++)
	{
		this->_order.push_back(jacobMax);
		// std::cout << "jacob size: " << _order << std::endl;	
	}
    this->printArr(this->_order, "order: ");
}

void PmergeMe::findPendingPair()
{

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

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		out << vec[i] << ", ";
	return (out);
}

size_t PmergeMe::arrSize(void)
{
	return (this->_arr.size());
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
