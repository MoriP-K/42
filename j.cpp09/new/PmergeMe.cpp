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

std::vector<data> PmergeMe::initData()
{
	std::vector<data> info;
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		data tmp;
		tmp.original_idx = i;
		tmp.value = this->_input_arr[i];
		info.push_back(tmp);
	}
	return (info);
}

void PmergeMe::startSorting(const std::vector<data>& info)
{
	std::vector<data> winner;
	std::vector<data> loser;

	if (info.size() == 1)
	{
		this->_sorted_vec.push_back(info[0]);
		return ;
	}

	comparePair(info, &winner, &loser);

	static size_t i = 0;
	i++;
	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "         BEFORE" << std::endl;
	std::cout << "\n-------- list ---------" << std::endl;
	printInfo(info, WHITE, false);
	// printNow(winner,loser);

	std::cout << "\nafter compare count: " << _count << std::endl;
	_total += _count;
	_count = 0;

	this->startSorting(winner);

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "          AFTER" << std::endl;
	std::cout << "\n-------- list ---------" << std::endl;
	printInfo(info, WHITE, false);
	// printNow(winner,loser);
	i--;

	std::vector<size_t> jacob = makeJacobsthalOrder(loser.size());
	std::cout << "jacob: " << jacob << std::endl;

	std::vector<size_t> order = generateInsertOrder(jacob, loser.size());
	std::cout << "order: " << order << std::endl;

	std::cout << "     SORTED BEFORE" << std::endl;
	printInfo(this->_sorted_vec, YELLOW, false);

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];

		std::cout << "\n   <<<<<< info[" << i <<"] >>>>>>" << std::endl;
		// printInfo(info, WHITE, false);
		if (i == 0)
		{
			std::cout << "idx == 0" << std::endl;
			int pair_idx = getIndexFromWinner(this->_sorted_vec[i].original_idx, winner);
			if (pair_idx == -1)
			{
				std::cout << "AAA" << std::endl;
				return ;
			}
			std::cout << "insert value(loser[" << pair_idx << "]): " << loser[pair_idx] << std::endl;
			this->_sorted_vec.insert(this->_sorted_vec.begin(), loser[pair_idx]);
			printInfo(this->_sorted_vec, YELLOW, false);
		}

		size_t loser_original_idx = loser[idx].original_idx;

		if (isAlreadyInserted(loser_original_idx))
		{
			std::cout << "LLL" << std::endl;
			continue ;
		}

		// to insert loser[idx]
		// std::cout << "order[" << i <<"] = " << idx << ", loser[" << idx <<"] = " << loser[idx] << std::endl;
		if (idx >= winner.size())
		{
			// skip searching for loser pair
			// size_t search_limit = this->_sorted_vec.size();
			// if (!winner.empty())
			// {
			// 	int last_winner_pos = getIndexFromDefeatedIdx(winner[winner.size() - 1].original_idx);
			// 	if (last_winner_pos != -1)
			// 		search_limit = last_winner_pos;
			// }
			// size_t insert_pos;
			// if (search_limit == this->_sorted_vec.size())
				size_t insert_pos = binarySearch(loser[idx].value);
			// else
			// 	insert_pos = limitedBinarySearch(search_limit, loser[idx].value);
			// std::cout << "insert pos: " << insert_pos << std::endl;
			std::cout << "::insert value(loser[" << idx << "]): " << loser[idx] << std::endl;
			this->_sorted_vec.insert(this->_sorted_vec.begin() + insert_pos, loser[idx]);
			printInfo(this->_sorted_vec, YELLOW, false);
			// printNow(winner, loser);
		}
		else
		{
			// printNow(winner, loser);
			// std::cout << "order[i] < winner.size()" << std::endl;
			int search_limit = getIndexFromDefeatedIdx(winner[idx].original_idx);
			if (search_limit == -1)
			{
				std::cout << "PPP" << std::endl;
				return ;
			}

			size_t insert_pos = limitedBinarySearch(search_limit, loser[idx].value); // --search_limit??
			// std::cout << "::insert pos: " << insert_pos << std::endl;
			std::cout << "insert value(loser[" << idx << "]): " << loser[idx] << std::endl;
			this->_sorted_vec.insert(this->_sorted_vec.begin() + insert_pos, loser[idx]);
			printInfo(this->_sorted_vec, YELLOW, false);
		}
		std::cout << "count[" << i << "]: " << _count << std::endl;
		_total += _count;
		_count = 0;
	}
	std::cout << "     SORTED AFTER" << std::endl;
	printInfo(this->_sorted_vec, YELLOW, false);
	std::cout << "TOTAL: " << _total << std::endl;
}

int PmergeMe::getInfoIndex(std::vector<data> info, std::vector<data> loser, size_t idx)
{
	for (size_t j = 0; j < info.size(); ++j)
	{
		if (loser[idx].original_idx == info[j].original_idx)
			return (j);
	}
	return (-1);
}

int PmergeMe::getIndexFromDefeatedIdx(size_t orig_idx)
{
	for (size_t j = 0; j < this->_sorted_vec.size(); ++j)
	{
		if (orig_idx == this->_sorted_vec[j].original_idx)
			return (j);
	}
	return (-1);
}
int PmergeMe::getIndexFromWinner(size_t orig_idx, std::vector<data> winner)
{
	for (size_t i = 0; i < winner.size(); ++i)
	{
		if (orig_idx == winner[i].original_idx)
			return (i);
	}
	return (-1);
}

int PmergeMe::getIndexFromLoser(size_t orig_idx, std::vector<data> loser)
{
	for (size_t i = 0; i < loser.size(); ++i)
	{
		if (orig_idx == loser[i].original_idx)
			return (i);
	}
	return (-1);
}

bool PmergeMe::isAlreadyInserted(size_t loser_orig_index)
{
	for (size_t i = 0; i < this->_sorted_vec.size(); ++i)
	{
		if (loser_orig_index == this->_sorted_vec[i].original_idx)
			return (true);
	}
	return (false);
}

size_t PmergeMe::searchLimitLength(std::vector<data> winner, size_t index)
{
	size_t len = 0;
	for (size_t j = 0; j < _sorted_vec.size(); ++j)
	{
		if (winner[index].original_idx == _sorted_vec[j].original_idx)
			break;
		++len; 
	}
	return (len);
}

void PmergeMe::comparePair(std::vector<data> info, std::vector<data> *winner, std::vector<data> *loser)
{
	for (size_t i = 0; i < info.size();)
	{
		if (i + 1 < info.size())
		{
			++this->_count;
			std::cout << "count: " << _count << std::endl;
			if (info[i].value > info[i + 1].value)
			{
				info[i].defeated_idx.push_back(i + 1);
				winner->push_back(info[i]);
				loser->push_back(info[i + 1]);
			}
			else
			{
				info[i + 1].defeated_idx.push_back(i);
				winner->push_back(info[i + 1]);
				loser->push_back(info[i]);
			}
		}
		else
		{
			loser->push_back(info[i]);
		}
		i += 2;
	}
}

std::vector<size_t> PmergeMe::makeJacobsthalOrder(size_t loser_len)
{
	std::vector<size_t> arr;
	size_t num = 0;
	size_t i = 2;

	arr.push_back(2); // 0
	if (loser_len < 2)
		return (arr);
	arr.push_back(2); // 0
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
	order.push_back(0);

	if (jacob.size() < 2)
		return (order);

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
	for (size_t i = 1; order.size() < loser_len; ++i)
	{
		std::vector<size_t> num;
		num.clear();
		for (size_t j = jacob[i - 1]; 0 < j; --j)
		{
			std::cout << "push num: " << value << std::endl;
			num.push_back(value);
			++value;
		}
		while (0 < num.size())
		{
			std::cout << "push order: " << num.back() << std::endl;
			order.push_back(num.back());
			num.pop_back();
		}
		std::cout << "order size: " << order.size() << ", loser len: " << loser_len << std::endl;
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

	int ng = -1;
	int ok = search_limit + 1;

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

void PmergeMe::printInfo(std::vector<data> info, const std::string& color, bool list_flag)
{
	size_t width = 5;
	for (size_t i = 0; i < info.size(); ++i)
	{
		std::ostringstream oss;
		oss << info[i].value;
		size_t tmp = oss.str().length();
		if (tmp > width)
			width = tmp;
	}
	std::cout <<  color;
	std::cout << std::right << std::setw(6) << "| index" << "| "
		<< std::setw(6) << "orig i" << "| "
		<< std::setw(width) <<  "value" << "|" << std::endl;
	for (size_t i = 0; i < info.size(); ++i)
	{
		std::cout << "| " << std::setw(5) << i << "| "
			<< std::right << std::setw(6) << info[i].original_idx << "| "
			<< std::setw(width) << info[i].value << "|" << std::endl;
	}
	if (list_flag)
	{
		for (size_t i = 0; i < info.size(); ++i)
		{
			if (!info[i].defeated_idx.empty())
			{
				std::cout << "value = " << info[i].value << "           (orig idx[" << info[i].original_idx << "])" << "\n  => defeat idx = ";
				std::cout << info[i].defeated_idx << std::endl;
			}
		}
	}
	std::cout << RESET;
}

void PmergeMe::printNow(std::vector<data> winner, std::vector<data> loser)
{
	std::cout << "======== Winner ========" << std::endl;
	printInfo(winner, RED, true);
	std::cout << "======== Loser ========" << std::endl;
	printInfo(loser, BLUE, true);
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
