#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->_count = 0;
	this->_depth = 0;
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

void PmergeMe::startSorting(const std::vector<data>& info, size_t depth)
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
	printNow(winner,loser);


	this->startSorting(winner, ++depth);

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "          AFTER" << std::endl;
	std::cout << "\n-------- list ---------" << std::endl;
	printInfo(info, WHITE, false);
	printNow(winner,loser);
	i--;

	std::vector<size_t> jacob = makeJacobsthalOrder(loser.size());
	std::cout << "jacob: " << jacob << std::endl;
	std::vector<size_t> order = generateInsertOrder(jacob, loser.size());

	std::cout << "order: " << order << std::endl;

	// size_t loser_len = loser.size();
	// std::cout << "loser len == " << loser_len << std::endl;

	std::cout << "     SORTED BEFORE" << std::endl;
	printInfo(this->_sorted_vec, YELLOW, false);

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];

		std::cout << "\n   <<<<<< info[" << i <<"] >>>>>>" << std::endl;
		printInfo(info, WHITE, false);
		if (i == 0)
		{
			size_t latest_loser_pair_idx = this->_sorted_vec[0].defeated_idx.back();
			this->_sorted_vec[0].defeated_idx.pop_back();
			for (size_t j = 0; j < winner.size(); ++j)
			{
				if (winner[j].original_idx == this->_sorted_vec[0].original_idx)
					winner[j].defeated_idx.pop_back();
			}
			this->_sorted_vec.insert(this->_sorted_vec.begin(), info[latest_loser_pair_idx]);
			// std::cout << "j: " << j << std::endl;
			std::cout << " = insert sorted-vec[0]-pair =" << std::endl;
			printInfo(this->_sorted_vec, YELLOW, false);
		}
		
		size_t loser_original_idx = loser[idx].original_idx;

		if (isAlreadyInserted(loser_original_idx))
			continue ;

		// to insert loser[idx]
		std::cout << "i = " << i << std::endl;
		if (i < this->_sorted_vec.size())
			std::cout << "sorted[" << i << "]: " << _sorted_vec[i] << std::endl;
		if (i < loser.size())
			std::cout << "loser[" << i << "]: " << loser[i] << std::endl;
		std::cout << "order[" << i <<"] = " << idx << ", loser[" << idx <<"] = " << loser[idx] << std::endl;
		if (idx >= winner.size())
		{
			std::cout << "here" << std::endl;
			// skip searching for loser pair
			std::cout << "insert value: " << loser[idx].value << std::endl;
			size_t insert_pos = binarySearch(loser[idx].value);
			std::cout << "insert pos: " << insert_pos << std::endl;
			this->_sorted_vec.insert(this->_sorted_vec.begin() + insert_pos, loser[idx]);
			printNow(winner, loser);
		}
		else
		{
			std::cout << "there" << std::endl;
			if (i < winner.size())
			{
				size_t latest_loser_pair_idx = winner[i].defeated_idx.back();
				size_t search_limit = searchLimitLength(winner, idx);
				std::cout << "::latest_loser_pair_idx: " << latest_loser_pair_idx << std::endl;

				std::cout << search_limit << std::endl;

				// for (size_t j = 0; j < search_limit; ++j)
					// std::cout << "for search limit: " << _sorted_vec[j] << std::endl;
				size_t insert_pos = limitedBinarySearch(search_limit, loser[idx].value);
				std::cout << "::insert pos: " << insert_pos << std::endl;
				this->_sorted_vec.insert(this->_sorted_vec.begin() + insert_pos, loser[idx]);
				printInfo(this->_sorted_vec, YELLOW, false);
			}
			else
			{
				int info_idx = getInfoIndex(info, loser, idx);
				if (info_idx == -1)
				{
					std::cout << "UUU" << std::endl;
					return ;
				}
				int search_limit = getIndexFromDefeatedIdx(depth, info_idx);
				if (search_limit == -1)
				{
					std::cout << "PPP" << std::endl;
					return ;
				}
				size_t insert_pos = limitedBinarySearch(search_limit, loser[idx].value);
				std::cout << "<<insert pos: " << insert_pos << std::endl;
				this->_sorted_vec.insert(this->_sorted_vec.begin() + insert_pos, loser[idx]);
				printInfo(this->_sorted_vec, YELLOW, false);
			}
		}
	}
	std::cout << "     SORTED AFTER" << std::endl;
	printInfo(this->_sorted_vec, YELLOW, false);

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

// ======== Loser ========
// | index| orig i| value|
// // |     0|      0|     3|
// // |     1|      2|     1|
// // |     2|      5|     2|
// // |     3|      7|    10|
// // |     4|      8|     7|
// // |     5|     11|     6|
// |     6|     13|     4|
// // |     7|     15|    11|
// // |     8|     16|    13|
// // |     9|     19|     5|
// // |    10|     20|     8|

int PmergeMe::getIndexFromDefeatedIdx(size_t depth, size_t loop_idx)
{
	for (size_t j = 0; j < this->_sorted_vec.size(); ++j)
	{
		if (depth == this->_sorted_vec[j].defeated_idx.size())
		{
			if (loop_idx == this->_sorted_vec[j].defeated_idx[depth - 1])
				return (j);
		}
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
		// std::cout << "win orig idx: " << winner[index].original_idx << ", sorted orig idx: " << _sorted_vec[j].original_idx << std::endl;
		if (winner[index].original_idx == _sorted_vec[j].original_idx)
			break;
		++len; 
	}
	return (len);
}

size_t PmergeMe::limitedBinarySearch(size_t search_limit, size_t search_value)
{
	if (search_limit == 0)
		return (0);

	int ng = -1;
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

void PmergeMe::comparePair(std::vector<data> info, std::vector<data> *winner, std::vector<data> *loser)
{
	for (size_t i = 0; i < info.size();)
	{
		if (i + 1 < info.size())
		{
			++this->_count;
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

	arr.push_back(0);
	if (loser_len < 2)
		return (arr);
	arr.push_back(1);
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

size_t PmergeMe::getDepth() const
{
	return (this->_depth);
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
