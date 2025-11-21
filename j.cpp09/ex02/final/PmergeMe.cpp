#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->_count = 0;
	this->_total = 0;
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
		this->_sorted_vec = src._sorted_vec;
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

void PmergeMe::initArr()
{
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		std::vector<size_t> tmp;
		tmp.push_back(i);
		this->_pair_orig_idx.push_back(tmp);
	}
}

void PmergeMe::startSorting(void)
{
	// std::vector<std::vector<size_t> > pair_orig_idx;
	std::vector<size_t> straggler_idx;

	if (this->_pair_orig_idx.size() == 1)
	{
		size_t len = this->_pair_orig_idx[0].size();
		for (size_t i = 0; i < this->_pair_orig_idx[0].size(); ++i)
			std::cout << this->_pair_orig_idx[0][i] << std::endl;
		std::cout << "len: " << len << std::endl;
		std::vector<size_t> tmp;
		for (size_t i = len / 2; i < len; ++i)
			tmp.push_back(this->_pair_orig_idx[0][i]);
		this->_pair_orig_idx[0].erase(_pair_orig_idx[0].begin() + len / 2, _pair_orig_idx[0].end());
		this->_pair_orig_idx.insert(_pair_orig_idx.begin(), tmp);
		return ;
	}

	comparePair(&straggler_idx);
	std::cout << "pair_orig_idx size: " << this->_pair_orig_idx.size() << std::endl;

	if (!straggler_idx.empty())
		std::cout << "straggler idx: " << straggler_idx << std::endl;

	static size_t i = 0;
	i++;

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "         BEFORE" << std::endl;
	std::cout << "\n-------- list ---------" << std::endl;
	printInfo(this->_pair_orig_idx, WHITE);

	// std::cout << "\nafter compare count: " << _count << std::endl;
	// _total += _count;
	// std::cout << "BEFORE TOTAL: " << _total << std::endl;
	// _count = 0;

	this->startSorting();

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "          AFTER" << std::endl;
	std::cout << "\n-------- list ---------" << std::endl;
	printInfo(this->_pair_orig_idx, WHITE);
	i--;

	// std::vector<size_t> jacob = makeJacobsthalOrder(this->_pair_orig_idx.size());
	// std::cout << "jacob: " << jacob << std::endl;

	// std::vector<size_t> order = generateInsertOrder(jacob, this->_pair_orig_idx.size());
	// std::cout << "order: " << order << std::endl;

	// std::cout << "     SORTED BEFORE" << std::endl;
	// printInfo(NULL, YELLOW, false);
}

void PmergeMe::comparePair(std::vector<size_t> *straggler)
{
	std::vector<std::vector<size_t> > arr;

	for (size_t i = 0; i < this->_pair_orig_idx.size();)
	{
		if (i + 1 < this->_pair_orig_idx.size())
		{
			std::vector<size_t> tmp;
			++this->_count;
			std::cout << "count: " << _count << std::endl;
			if (this->_input_arr[this->_pair_orig_idx[i][0]] > this->_input_arr[this->_pair_orig_idx[i + 1][0]])
			{
				tmp.insert(tmp.end(), this->_pair_orig_idx[i].begin(),
					this->_pair_orig_idx[i].end());
				tmp.insert(tmp.end(), this->_pair_orig_idx[i + 1].begin(),
					this->_pair_orig_idx[i + 1].end());
			}
			else
			{
				tmp.insert(tmp.end(), this->_pair_orig_idx[i + 1].begin(),
					this->_pair_orig_idx[i + 1].end());
				tmp.insert(tmp.end(), this->_pair_orig_idx[i].begin(),
					this->_pair_orig_idx[i].end());
			}
			arr.push_back(tmp);
		}
		else
		{
			straggler->push_back(i);
		}
		i += 2;
	}
	this->_pair_orig_idx.clear();
	for (size_t i = 0; i < arr.size(); ++i)
	{
		this->_pair_orig_idx.push_back(arr[i]);
	}
}

std::vector<size_t> PmergeMe::makeJacobsthalOrder(size_t loser_len)
{
	std::vector<size_t> arr;
	size_t num = 0;
	size_t i = 2;

	std::cout << "loser len: " << loser_len << std::endl; 
	arr.push_back(2); // 0
	if (loser_len < 2)
	{
		std::cout << "EEE" << std::endl;
		return (arr);
	}
	// arr.push_back(2); // 0
	while (1)
	{
		num = arr[i - 1] + arr[i - 2] * 2;
		if (num < loser_len)
			arr.push_back(num);
		else
			break;
		++i;
	}
	return (arr);
}

std::vector<size_t> PmergeMe::generateInsertOrder(std::vector<size_t> jacob, size_t loser_len)
{
	std::vector<size_t> order;

	if (loser_len < 2)
	{
		order.push_back(0);
		return (order);
	}

	if (loser_len == 2)
	{
		order.push_back(0);
		order.push_back(1);
		return (order);
	}

	size_t jacob_len = jacob.size();
	size_t jacob_max = jacob[jacob_len - 1];

	// for (size_t i = 0; i < jacob_len; ++i)
	// {
	// 	for (size_t j = jacob[i]; 0 < j; --j)
	// 	{
	// 		order.push_back(j);
	// 	}
	// 	// for (size_t j = jacob[i] + 1; 0 < j && order.size() <= loser_len; --j)
	// 	// {
	// 	// 	order.push_back(j);
	// 	// }
	// }

	// aaa
	size_t value = 1;
	order.push_back(0);
	for (size_t i = 1; order.size() < loser_len; ++i)
	{
		std::vector<size_t> num;
		num.clear();
		for (size_t j = jacob[i - 1]; 0 < j; --j)
		{
			// std::cout << "push num: " << value << std::endl;
			num.push_back(value);
			++value;
		}
		while (0 < num.size())
		{
			// std::cout << "push order: " << num.back() << std::endl;
			order.push_back(num.back());
			num.pop_back();
		}
		// std::cout << "order size: " << order.size() << ", loser len: " << loser_len << std::endl;
	}
	// aaa

	size_t loser_idx = loser_len - 1;
	while (loser_idx > jacob_max)
	{
		order.push_back(loser_idx);
		--loser_idx;
	}
	return (order);
}

size_t PmergeMe::limitedBinarySearch(size_t search_limit, size_t search_value)
{
	if (search_limit == 0)
		return (0);

	int ng = 0;
	int ok = search_limit;

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOK(mid, search_value))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

int PmergeMe::binarySearch(int key)
{
	int ng = 0;
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
	std::cout << "count: " << _count << std::endl;
	std::cout << "compare: " << _sorted_vec[index].value << " ? " << key << std::endl;
	if (_sorted_vec[index].value >= key)
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

const std::vector<std::vector<size_t> > PmergeMe::getPairOrigIdx() const
{
	return (this->_pair_orig_idx);
}

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		out << vec[i] << " ";
	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
		out << vec[i] << " ";
	return (out);
}

std::ostream &operator<<(std::ostream &out, const data &vec)
{
	out << WHITE << "value: " << vec.value << ", orig idx: " << vec.original_idx << RESET;
	return (out);
}

void invalidArgument(void)
{
	std::cout << "Usage: ./PmergeMe <num> ..." << std::endl;
}

///////////
// DEBUG //
///////////

void PmergeMe::printInfo(std::vector<std::vector<size_t> > arr, const std::string& color)
{
	size_t width = 5;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::ostringstream oss;
		oss << arr[i];
		size_t tmp = oss.str().length();
		if (tmp > width)
			width = tmp;
	}
	std::cout <<  color;
	std::cout << std::right << std::setw(6) << "| index" << "| "
		<< std::setw(6) << "orig i" << "| "
		<< std::setw(width) <<  "value" << "|" << std::endl;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		std::cout << "| " << std::setw(5) << i << "| "
			<< std::right << std::setw(6) << arr[i][0] << "| "
			<< std::setw(width) << this->_input_arr[arr[i][0]] << "|" << std::endl;
	}
	std::cout << RESET;
}

// void PmergeMe::printNow(std::vector<data> winner, std::vector<data> loser)
// {
// 	std::cout << "======== Winner ========" << std::endl;
// 	printInfo(winner, RED, true);
// 	std::cout << "======== Loser ========" << std::endl;
// 	printInfo(loser, BLUE, true);
// }

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
