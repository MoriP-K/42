#include "PmergeMe.hpp"

void PmergeMe::printCount()
{
	std::cout << "count: " << this->_count << std::endl;
}

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->_count = 0;
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

void PmergeMe::MIS(std::vector<int> arr)
{
	std::vector<int> main;
	std::vector<int> pending;
	std::vector<int> mainPositoins;
	int straggler = -1;

	if (arr.size() == 1)
	{
			this->_sortedVec.push_back(arr[0]);
		return ;
	}
	for (std::vector<int>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		if (it + 1 != arr.end())
		{
			if (*it < *(it + 1))
			{
				main.push_back(*(it + 1));
				pending.push_back(*it);
				// pendingToMain[*it] = *(it + 1);
			}
			else
			{
				main.push_back(*it);
				pending.push_back(*(it + 1));
				// pendingToMain[*(it + 1)] = *it;
			}
			++this->_count;
			std::cout << _count << std::endl;
			++it;
		}
		else
			// pending.push_back(*it);
			straggler = *it;
	}

	this->MIS(main);

	printArr(main, "main: ");
	printArr(pending, "pend: ");
	printArr(_sortedVec, "sort: ");

	size_t pendingLen = pending.size();
	if (pendingLen < 1 || arr.size() < 2)
		return ;
	std::vector<int> jacob = this->generateJacobsthal(pendingLen);
    std::vector<int> order = this->createInsertionOrder(jacob, pendingLen);
	// printArr(order, "order: ");
	std::map<int, int> insertedPos;
	for (std::vector<int>::iterator it = order.begin(); it != order.end(); ++it)
	{
		std::cout << "order: " << *it << std::endl;
		std::cout << "value: " << pending[*it] << std::endl;
		if (*it == 0)
		{
			this->_sortedVec.insert(this->_sortedVec.begin(), pending[*it]);
			printArr(_sortedVec, "push front sorted: ");
			continue;
		}
		int sortedPos = this->searchPositionFromSorted(main[*it]);
		if (sortedPos < 0)
			throw ErrorException();
		int insertPos = this->limitedBinarySearch((size_t)sortedPos, pending[*it]);
		if (insertPos != -1)
		{
			this->_sortedVec.insert(this->_sortedVec.begin() + insertPos, pending[*it]);
			printArr(_sortedVec, "sorted: ");
		}
	}
	if (straggler != -1)
	{
		// if (straggler < this->_sortedVec.front())
		// {
		// 	this->_sortedVec.insert(this->_sortedVec.begin(), straggler);
		// }
		// else if (this->_sortedVec.back() < straggler)
		// {
		// 	this->_sortedVec.push_back(straggler);
		// }	
		// else
		// {
			int pos = this->binarySearch(straggler);
			this->_sortedVec.insert(this->_sortedVec.begin() + pos, straggler);
		// }
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
			if (vec[i - 2] * 2 + vec[i - 1] >= size)
				break;
			else
				vec.push_back(vec[i - 2] * 2 + vec[i - 1]);
		}
		i++;
	}
	vec.erase(vec.begin(), vec.begin() + 2);
	return (vec);
}

std::vector<int> PmergeMe::createInsertionOrder(std::vector<int> jacob, size_t pendingLength)
{
	std::vector<int> order;

	order.push_back(0);
	if (jacob.empty())
		return order;

	size_t length = pendingLength;
	size_t jacobSize = jacob.size();
	size_t jacobMax = jacob[jacobSize - 1];
    for (size_t i = jacobSize; 0 < i; --i)
    {
		int n = i - 1;
        int bigger = jacob[n];
		int smaller = (n > 0) ? jacob[n - 1] + 1 : 1;

        while (smaller <= bigger && bigger < (int)length)
        {
            order.push_back(bigger);
            bigger--;
        }
    }
	while (--length > jacobMax)
	{
		order.push_back(length);
	}
	// while (length > jacobMax + 1)
	// {
	// 	++jacobMax;
	// 	order.push_back(jacobMax);
	// }
	return (order);
}

int PmergeMe::searchPositionFromSorted(int mainValue)
{
	for (size_t i = 0; i < this->_sortedVec.size(); ++i)
	{
		if (mainValue == this->_sortedVec[i])
			return (i);
	}
	return (-1);
}

int PmergeMe::limitedBinarySearch(size_t len, int key)
{
	int left = -1;
	int right = (int)len;

	while (abs(right - left) > 1)
	{
		int mid = (right + left) / 2;

		if (isOK(mid, key))
			right = mid;
		else
			left = mid;
	}
	return (right);
}

int PmergeMe::binarySearch(int key)
{
	int ng = -1;
	int ok = (int)_sortedVec.size();

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOK(mid, key))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

bool PmergeMe::isOK(int index, int key)
{
	++this->_count;
	std::cout << _count << std::endl;
	if (_sortedVec[index] >= key)
		return (true);
	return (false);
}

const std::vector<int> PmergeMe::getArr() const
{
	return (this->_arr);
}

const std::vector<int> PmergeMe::getSorted() const
{
	return (this->_sortedVec);
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
			std::cout << *it << " ";
	std::cout << std::endl;
}
