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
	std::vector<size_t> main_index;
	std::vector<size_t> pend_index;
	std::vector<int> positions(arr.size());
	// int straggler_idx = -1;

	for (size_t i = 0; i < arr.size(); ++i)
		positions[i] = -1;
	if (arr.size() == 1)
	{
		this->_sorted_vec.push_back(arr[0]);
		return ;
	}
	int k = 0;
	for (size_t i = 0; i < arr.size(); )
	{
		if (i + 1 < arr.size())
		{
			if (arr[i] < arr[i + 1])
			{
				main_index.push_back(i + 1);
				pend_index.push_back(i);
			}
			else
			{
				main_index.push_back(i);
				pend_index.push_back(i + 1);
			}
			++this->_count;
			// std::cout << _count << std::endl;
			i += 2;
		}
		else
		{
			// straggler_idx = i;
			pend_index.push_back(i);
			break ;
		}
	}
	std::cout << "===== k = " << k++ << " =====" << std::endl;
	std::cout << "main idx: " << main_index << std::endl;
	std::cout << "main val: ";
	for (size_t i = 0; i < main_index.size(); ++i)
		std::cout << _arr[main_index[i]] << std::endl;
	std::cout << "pend idx: " << pend_index << std::endl;
	for (size_t i = 0; i < pend_index.size(); ++i)
		std::cout << _arr[pend_index[i]] << std::endl;
	std::cout << std::endl;

	std::vector<size_t> mainValues;
	for (size_t i = 0; i < main_index.size(); ++i)
		mainValues.push_back(arr[main_index[i]]);

	// size_t sortedSizeBefore = this->_sorted_vec.size();
	this->MIS(mainValues);

	printArr(main_index, "main_index: ");
	printArr(pend_index, "pend_index: ");
	printArr(_sorted_vec, "sort: ");
	std::cout << std::endl;

	// for (size_t i = 0; i < main_index.size(); ++i)
	// 	positions[main_index[i]] = sortedSizeBefore + i;
	size_t pending_len = pend_index.size();
	if (pending_len < 1)
		return ;
	std::vector<int> jacob = this->generateJacobsthal(pending_len);
    std::vector<int> order = this->createInsertionOrder(jacob, pending_len);
	std::cout << "order: " << order << std::endl;
	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		std::cout << "pend index: " << pend_index[idx] << std::endl;
		std::cout << "value: " << arr[pend_index[idx]] << std::endl;
		// size_t pendIdx = pend_index[idx];
		// size_t mainIdx = main_index[idx];
		// int sortedPos = positions[mainIdx];
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

std::vector<int> PmergeMe::createInsertionOrder(std::vector<int> jacob, size_t pending_len)
{
	std::vector<int> order;

	order.push_back(0);
	if (jacob.empty())
		return order;

	size_t length = pending_len;
	size_t jacob_size = jacob.size();
	size_t jacob_max = jacob[jacob_size - 1];
    for (size_t i = jacob_size; 0 < i; --i)
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
	while (--length > jacob_max)
	{
		order.push_back(length);
	}
	// while (length > jacob_max + 1)
	// {
	// 	++jacob_max;
	// 	order.push_back(jacob_max);
	// }
	return (order);
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
	int ok = (int)_sorted_vec.size();

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
	if (_sorted_vec[index] >= key)
		return (true);
	return (false);
}

const std::vector<size_t> PmergeMe::getArr() const
{
	return (this->_arr);
}

const std::vector<size_t> PmergeMe::getSorted() const
{
	return (this->_sorted_vec);
}

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		out << vec[i] << ", ";
	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec)
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
