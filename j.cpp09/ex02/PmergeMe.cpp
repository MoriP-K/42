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

void PmergeMe::MIS(std::vector<size_t> arr)
{
	std::vector<size_t> main;
	std::vector<size_t> pending;
	std::vector<int> positions(arr.size());
	int straggler_idx = -1;

	for (size_t i = 0; i < arr.size(); ++i)
		positions[i] = -1;
	if (arr.size() == 1)
	{
		this->_sortedVec.push_back(arr[0]);
		return ;
	}
	for (size_t i = 0; i < arr.size(); )
	{
		if (i + 1 < arr.size())
		{
			if (arr[i] < arr[i + 1])
			{
				main.push_back(i + 1);
				pending.push_back(i);
			}
			else
			{
				main.push_back(i);
				pending.push_back(i + 1);
			}
			++this->_count;
			// std::cout << _count << std::endl;
			i += 2;
		}
		else
		{
			straggler_idx = i;
			break ;
		}
	}

	if (main.empty())
	{
		if (straggler_idx != -1)
			this->_sortedVec.push_back(arr[straggler_idx]);
		return ;
	}

	std::vector<size_t> mainValues;
	for (size_t i = 0; i < main.size(); ++i)
		mainValues.push_back(arr[main[i]]);

	size_t sortedSizeBefore = this->_sortedVec.size();
	this->MIS(mainValues);

	printArr(main, "main: ");
	printArr(pending, "pend: ");
	printArr(_sortedVec, "sort: ");

	for (size_t i = 0; i < main.size(); ++i)
		positions[main[i]] = sortedSizeBefore + i;
	size_t pendingLen = pending.size();
	if (pendingLen < 1)
		return ;
	std::vector<int> jacob = this->generateJacobsthal(pendingLen);
    std::vector<int> order = this->createInsertionOrder(jacob, pendingLen);
	std::cout << "order: " << order << std::endl;
	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		std::cout << "order: " << i << std::endl;
		std::cout << "value: " << arr[pending[idx]] << std::endl;
		size_t pendIdx = pending[idx];
		size_t mainIdx = main[idx];
		int sortedPos = positions[mainIdx];
		if (idx == 0)
		{
			this->_sortedVec.insert(this->_sortedVec.begin() + sortedPos, arr[pendIdx]);
			for (size_t j = 0; j < main.size(); ++j)
			{
				if (positions[main[j]] >= sortedPos)
					positions[main[j]]++;
			}
			printArr(_sortedVec, "push front sorted: ");
			continue;
		}
		// int sortedPos = this->searchPositionFromSorted(main[i]);
		// if (sortedPos < 0)
		// 	throw ErrorException();
		int insertPos = this->limitedBinarySearch((size_t)sortedPos, arr[pendIdx]);
		if (insertPos != -1)
		{
			this->_sortedVec.insert(this->_sortedVec.begin() + insertPos, arr[pendIdx]);
			for (size_t j = 0; j < main.size(); ++j)
			{
				if (positions[main[j]] >= insertPos)
					positions[main[j]]++;
			}
			printArr(_sortedVec, "sorted: ");
		}
	}
	if (straggler_idx != -1)
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
			int pos = this->binarySearch(arr[straggler_idx]);
			this->_sortedVec.insert(this->_sortedVec.begin() + pos, arr[straggler_idx]);
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
	std::cout << "jacob: " << jacob << std::endl;
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
	// while (--length > jacobMax)
	// {
	// 	order.push_back(length);
	// }
	while (length > jacobMax + 1)
	{
		++jacobMax;
		order.push_back(jacobMax);
	}
	return (order);
}

int PmergeMe::searchPositionFromSorted(size_t mainValue)
{
	for (size_t i = 0; i < this->_sortedVec.size(); ++i)
	{
		if (mainValue == this->_sortedVec[i])
			return (i);
	}
	return (-1);
}

int PmergeMe::limitedBinarySearch(size_t len, size_t key)
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

bool PmergeMe::isOK(int index, size_t key)
{
	++this->_count;
	std::cout << _count << std::endl;
	if (_sortedVec[index] >= key)
		return (true);
	return (false);
}

const std::vector<size_t> PmergeMe::getArr() const
{
	return (this->_arr);
}

const std::vector<size_t> PmergeMe::getSorted() const
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

void PmergeMe::printArr(std::vector<size_t> vec, std::string msg)
{
	std::cout << msg;
	for (std::vector<size_t>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
	std::cout << std::endl;
}
