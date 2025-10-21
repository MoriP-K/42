#include "PmergeMe.hpp"

int count = 0;

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->_straggler = -1;
}

void PmergeMe::mergeInsertionSort(void)
{
	this->dividePendingIntoMain(this->_arr);
	this->recursiveSort(this->_main);
	this->mergePendingToMain();
	// std::cout << "count: " << count << std::endl;
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

void PmergeMe::dividePendingIntoMain(std::vector<int> arr)
{
	if (arr.size() < 2)
	{
		this->_main.push_back(arr[0]);
		return;
	}
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
			count++;
			++it;
		}
		else
			this->_straggler = *it;
	}
	printArr(_main, "\nwinner: ");
	printArr(_pending, "loser : ");
	std::cout << std::endl;
	// printArr(_sortedVec, "sorted : ");
}

void PmergeMe::recursiveSort(std::vector<int> arr)
{
	std::vector<int> main;
	std::vector<int> pending;

	if (arr.size() < 2)
	{
		_sortedVec.push_back(arr[0]);
		return ;
	}

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
			}
			else
			{
				main.push_back(*it);
				pending.push_back(*(it + 1));
			}
			count++;
			++it;
		}
		else
			pending.push_back(*it);
	}
	printArr(main, "\nmain: ");
	printArr(pending, "pending: ");
	std::cout << std::endl;
	recursiveSort(main);

	if (pending.empty())
		return;
	size_t pendingLen = pending.size();
	std::cout << "pending len: " << pendingLen << std::endl;
	std::vector<int> jacob = generateJacobsthal(pendingLen);
	std::cout << "jacob: " << jacob << std::endl;
	std::vector<int> order = this->createInsertionOrder(jacob, pendingLen);
	std::cout << "recursive order: " << order << std::endl;

	for (std::vector<int>::iterator it = order.begin(); it != order.end(); ++it)
	{
		if (*it == 0)
			this->_sortedVec.insert(this->_sortedVec.begin(), pending[*it]);
		else
		{
			int pos = binarySearch(pending[*it]);
			if (pos != -1)
			_sortedVec.insert(_sortedVec.begin() + pos, pending[*it]);
		}
	}
}

void PmergeMe::mergePendingToMain()
{
	size_t pendingLen = this->_pending.size();
	if (pendingLen < 1 || _arr.size() < 2)
		return ;
	std::vector<int> jacob = this->generateJacobsthal(pendingLen);
    this->_order = this->createInsertionOrder(jacob, pendingLen);
	for (std::vector<int>::iterator it = this->_order.begin(); it != this->_order.end(); ++it)
	{
		if (*it == 0)
		{
			_sortedVec.insert(_sortedVec.begin(), this->_pending[*it]);
			continue;
		}
		int mainPair = this->findPendingPair(this->_pending[*it]);
		int sortedPos = this->searchPositionFromSorted(mainPair);
		if (sortedPos < 0)
		{
			std::cout << "DDD" << std::endl;
			throw ErrorException();
		}
		int insertPos = this->limitedBinarySearch((size_t)sortedPos, this->_pending[*it]);
		if (insertPos != -1)
			_sortedVec.insert(_sortedVec.begin() + insertPos, this->_pending[*it]);
	}
	if (this->_straggler != -1)
	{
		int pos = this->binarySearch(this->_straggler);
		this->_sortedVec.insert(_sortedVec.begin() + pos, this->_straggler);
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
	return (vec);
}

std::vector<int> PmergeMe::createInsertionOrder(std::vector<int> jacob, size_t pendingLength)
{
	std::vector<int> order;

	order.push_back(0);
	if (jacob.empty())
		return order;

	// size_t pendingLen = this->_pending.size();
	size_t jacobSize = jacob.size();
	size_t jacobMax = jacob[jacobSize - 1];
    for (size_t i = jacobSize; 0 < i; --i)
    {
		int n = i - 1;
        int bigger = jacob[n];
		int smaller = (n > 0) ? jacob[n - 1] + 1 : 1;

        while (smaller <= bigger && bigger < (int)pendingLength)
        {
            order.push_back(bigger);
            bigger--;
        }
    }
	// while (--pendingLength > jacobMax)
	// {
	// 	this->_order.push_back(pendingLength);
	// }
	while (pendingLength > jacobMax + 1)
	{
		++jacobMax;
		order.push_back(jacobMax);
	}
    // this->printArr(this->_order, "order: ");
	// printArr(_pending, "pending: ");
	// printArr(_sortedVec, "sorted : ");
	// if (this->_straggler)
	// 	std::cout << "straggler: " << this->_straggler << std::endl;
	return (order);
}

int PmergeMe::findPendingPair(int pending_value)
{
	std::map<int, int>::iterator it =_pendingToMain.find(pending_value);
	if (it != _pendingToMain.end())
		return (it->second);
	throw ErrorException();
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
	count++;
	if (_sortedVec[index] >= key)
		return (true);
	return (false);
}

size_t PmergeMe::getSearchLength(int mainValue)
{
	size_t len = 0;
	while (_sortedVec[len] != mainValue)
		len++;
	return (len);
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
