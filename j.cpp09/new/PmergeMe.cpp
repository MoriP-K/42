#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->initData();
	std::cout << "======== input ========" << std::endl;
	std::cout << this->_info << std::endl; // dd
	this->_count = 0;
	this->startSorting(this->_info);
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
	long num = 0;

	for (size_t i = 1; av[i]; ++i)
	{
		for (size_t j = 0; av[i][j]; ++j)
		{
			if (!isdigit(av[i][j]))
				return (false);
		}
		num = std::atol(av[i]);
		if (num < 0 || __INT_MAX__ < num)
			return (false);
		this->_input_arr.push_back(num);
	}
	return (true);
}

void PmergeMe::initData(void)
{
	data info;
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		info.original_idx = i;
		info.value = this->_input_arr[i];
		this->_info.push_back(info);
	}
}
void printNow(std::vector<data> winner, std::vector<data> loser);

void PmergeMe::startSorting(std::vector<data> info)
{
	std::vector<data> winner;
	std::vector<data> loser;

	if (info.size() == 1)
	{
		this->_sorted_vec.push_back(info[0]);
		return ;
	}

	for (size_t i = 0; i < info.size();)
	{
		if (i + 1 < info.size())
		{
			if (info[i].value > info[i + 1].value)
			{
				info[i].defeated_idx.push_back(i + 1);
				winner.push_back(info[i]);
				loser.push_back(info[i + 1]);
			}
			else
			{
				info[i + 1].defeated_idx.push_back(i);
				winner.push_back(info[i + 1]);
				loser.push_back(info[i]);
			}
		}
		else
		{
			loser.push_back(info[i]);
		}
		i += 2;
	}

	static size_t i = 0;
	i++;
	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "         BEFORE" << std::endl;
	printNow(winner,loser);

	this->startSorting(winner);

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "          AFTER" << std::endl;
	printNow(winner,loser);
	i--;

	std::vector<size_t> jacob = makeJacobsthalOrder(loser.size());
	std::vector<size_t> order = generateInsertOrder(jacob, loser.size());
	

	std::cout << "jacob: " << jacob << std::endl;
	std::cout << "order: " << order << std::endl;
}

std::vector<size_t> PmergeMe::makeJacobsthalOrder(size_t loser_len)
{
	std::vector<size_t> arr;
	size_t num = 0;
	size_t i = 1;

	arr.push_back(0);
	if (loser_len < 2)
		return (arr);
	arr.push_back(1);
	while (1)
	{
		num = arr[i] + arr[i - 1] * 2;
		if (num < loser_len)
			arr.push_back(num);
		else
			return (arr);
		++i;
	}
}

std::vector<size_t> PmergeMe::generateInsertOrder(std::vector<size_t> jacob, size_t loser_len)
{

	std::vector<size_t> order;
	order.push_back(0);

	if (jacob.size() < 2)
		return (order);

	size_t jacob_idx = jacob.size() - 1;
	size_t jacob_max = jacob[jacob_idx];

	while (0 < jacob_idx)
	{
		size_t bigger = jacob[jacob_idx];
		size_t smaller = jacob[jacob_idx - 1] + 1;

		while (bigger >= smaller)
		{
			order.push_back(bigger);
			--bigger;
		}
		--jacob_idx;
	}

	size_t bigger_idx = loser_len - 1;

	while (jacob_max < bigger_idx)
	{
		order.push_back(bigger_idx);
		--bigger_idx;
	}
	return (order);
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
	if (_sorted_vec[index].original_idx >= key)
		return (true);
	return (false);
}

const std::vector<size_t> PmergeMe::getArr() const
{
	return (this->_input_arr);
}

const std::vector<data> PmergeMe::getSorted() const
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

std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec)
{
	size_t width = 5;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::ostringstream oss;
		oss << vec[i].value;
		size_t tmp = oss.str().length();
		if (tmp > width)
			width = tmp;
	}
	out << std::right << std::setw(6) << "| index" << "| "
		<< std::setw(6) << "orig i" << "| "
		<< std::setw(width) <<  "value" << "|" << std::endl;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		out << "| " << std::setw(5) << i << "| "
			<< std::right << std::setw(6) << vec[i].original_idx << "| "
			<< std::setw(width) << vec[i].value << "|" << std::endl;
	}
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (!vec[i].defeated_idx.empty())
		{
			std::cout << "value = " << vec[i].value << "           (orig idx[" << vec[i].original_idx << "])" << "\n  => defeat idx = ";
			std::cout << vec[i].defeated_idx << std::endl;
		}
	}
	return (out);
}

void invalidArgument(void)
{
	std::cout << "Usage: ./PmergeMe <num> ..." << std::endl;
}

///////////
// DEBUG //
///////////

void printNow(std::vector<data> winner, std::vector<data> loser)
{
	std::cout << "======== Winner ========" << std::endl;
	std::cout << winner << std::endl;
	std::cout << "======== Loser ========" << std::endl;
	std::cout << loser << std::endl;
}

size_t PmergeMe::arrSize(void)
{
	return (this->_input_arr.size());
}

void PmergeMe::printArr(std::vector<size_t> vec, std::string msg)
{
	std::cout << msg;
	for (std::vector<size_t>::iterator it = vec.begin(); it != vec.end(); ++it)
			std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printCount()
{
	std::cout << "count: " << this->_count << std::endl;
}
