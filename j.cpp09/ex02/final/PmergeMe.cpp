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
		data tmp;
		for (size_t j = 0; av[i][j]; ++j)
		{
			if (!isdigit(av[i][j]))
				return (false);
		}
		num = std::atol(av[i]);
		if (num < 0 || __INT_MAX__ < num)
			return (false);
		tmp.value = num;
		this->_input_arr.push_back(tmp);
	}
	return (true);
}

void PmergeMe::initArr()
{
	// std::vector<std::vector<data> > tmp;
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		std::vector<data> tmp;
		data d_tmp;
		d_tmp.original_idx = i;
		tmp.push_back(d_tmp);
		this->_pair_orig_idx.push_back(tmp);
	}
}

void PmergeMe::startSorting(void)
{
	std::vector<data> straggler_idx;

	if (this->_pair_orig_idx.size() == 1)
	{
		std::cout << "return" << std::endl;
		return ;
	}

	static size_t i = 0;
	i++;

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "         BEFORE" << std::endl;

	straggler_idx = comparePair();
	// std::cout << "after compare arr size: " << this->_pair_orig_idx.size() << std::endl;

	if (!straggler_idx.empty())
	{
		std::cout << "\nstraggler [orig_idx]orig_value: \n" ;
		for (size_t i = 0; i < straggler_idx.size(); ++i)
			std::cout << "[" << straggler_idx[i].original_idx << "]" << this->_input_arr[straggler_idx[i].original_idx].value << ", ";
		std::cout << std::endl;
	}


	// std::cout << "\nafter compare count: " << _count << std::endl;
	// _total += _count;
	// std::cout << "BEFORE TOTAL: " << _total << std::endl;
	// _count = 0;

	this->startSorting();

	std::cout << "\n////////// [" << i << "] //////////" << std::endl;
	std::cout << "          AFTER" << std::endl;
	for (size_t i = 0; i < this->_pair_orig_idx.size(); ++i)
		std::cout << "[" << i << "]" << this->_input_arr[this->_pair_orig_idx[i][0].original_idx].value << " ";
	std::cout << std::endl;
	i--;

	std::vector<std::vector<data> > tmp;
	for (size_t i = 0; i < this->_pair_orig_idx.size(); ++i)
	{
		std::cout << "arr size: " << this->_pair_orig_idx[i].size() << std::endl;
		size_t center_idx = this->_pair_orig_idx[i].size() / 2;
		std::vector<data> vec;
		data d_tmp;
		for (size_t j = center_idx; j < this->_pair_orig_idx[i].size(); ++j)
		{
			d_tmp.original_idx = this->_pair_orig_idx[i][j].original_idx;
			d_tmp.defeated_orig_idx = this->_pair_orig_idx[i][j].defeated_orig_idx;
			vec.push_back(d_tmp);
		}
		tmp.push_back(vec);
		this->_pair_orig_idx[i].erase(this->_pair_orig_idx[i].begin() + center_idx, this->_pair_orig_idx[i].end());
	}
	if (!straggler_idx.empty())
	{
		for (size_t i = 0; i < straggler_idx.size(); ++i)
			std::cout << "straggler: [" << straggler_idx[i].original_idx << "]" << this->_input_arr[straggler_idx[i].original_idx].value << std::endl;
		tmp.push_back(straggler_idx);
	}

	std::vector<size_t> jacob = makeJacobsthalOrder(tmp.size());
	std::cout << "jacob: " << jacob << std::endl;

	std::vector<size_t> order = generateInsertOrder(jacob, tmp.size());
	std::cout << "order: " << order << std::endl;

	std::cout << "tmp size: " << tmp.size() << std::endl;
	for (size_t i = 0; i < tmp.size(); ++i)
	{
		std::cout << "tmp[" << i << "][0] " << this->_input_arr[tmp[i][0].original_idx].value << std::endl;
	}

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		int insert_pos = 0;
		if (idx == 0)
		{
			this->_pair_orig_idx.insert(this->_pair_orig_idx.begin(), tmp[idx]);
			tmp[i].erase(tmp[idx].begin(), tmp[idx].end());
			printArrAfterSorting();
			continue;
		}
		if (idx < order.size() - 1)
		{
			std::cout << "with pair" << std::endl;
			std::cout << "orig idx: " << tmp[idx][0].original_idx << ", value: " << _input_arr[tmp[idx][0].original_idx].value << std::endl;
			for (size_t j = 0; j < _pair_orig_idx[i].size(); ++j)
				std::cout << this->_pair_orig_idx[i][j].original_idx << std::endl;
			int search_limit = getIndexFromVector(tmp[idx][0].original_idx, this->_pair_orig_idx);
			if (search_limit == -1)
			{
				std::cout << "MMM" << std::endl;
				return ;
			}
			insert_pos = limitedBinarySearch(search_limit, this->_input_arr[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
			std::cout << "insert pos: " << insert_pos << std::endl;
		}
		else
		{
			std::cout << "no pair" << std::endl;
			insert_pos = binarySearch(this->_input_arr[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
			std::cout << "::insert pos: " << insert_pos << std::endl;
		}
		this->_pair_orig_idx.insert(this->_pair_orig_idx.begin() + insert_pos, tmp[idx]);
		printArrAfterSorting();
	}

	// for (size_t i = 0; i < this->_pair_orig_idx.size(); ++i)
	// {
	// 	// std::cout << "[" << i << "]: ";
	// 	for (size_t j = 0; j < this->_pair_orig_idx[i].size(); ++j)
	// 	{
	// 		std::cout << this->_input_arr[this->_pair_orig_idx[i][j].original_idx].value << " ";
	// 	}
	// }
	// std::cout << std::endl;

	// std::cout << "     SORTED BEFORE" << std::endl;
	// printInfo(NULL, YELLOW, false);
}

std::vector<data> PmergeMe::comparePair(void)
{
	std::vector<std::vector<data> > arr;
	std::vector<data> straggler;

	for (size_t i = 0; i < this->_pair_orig_idx.size();)
	{
		if (i + 1 < this->_pair_orig_idx.size())
		{
			std::vector<data> tmp;
			++this->_count;
			std::cout << "(" << (i + 2) / 2 << ") "
				<< this->_input_arr[this->_pair_orig_idx[i][0].original_idx].value
				<< " vs " << this->_input_arr[this->_pair_orig_idx[i + 1][0].original_idx].value
				<< std::endl;
			data d_tmp;
			if (this->_input_arr[this->_pair_orig_idx[i][0].original_idx].value > this->_input_arr[this->_pair_orig_idx[i + 1][0].original_idx].value)
			{
				this->_pair_orig_idx[i][0].defeated_orig_idx.push_back(this->_pair_orig_idx[i + 1][0].original_idx);
				d_tmp.value = this->_input_arr[this->_pair_orig_idx[i][0].original_idx].value;
				d_tmp.original_idx = this->_pair_orig_idx[i][0].original_idx;
				d_tmp.defeated_orig_idx = this->_pair_orig_idx[i][0].defeated_orig_idx;
				// d_tmp.defeated_orig_idx.push_back(this->_pair_orig_idx[i + 1][0].original_idx);
				tmp.insert(tmp.end(), this->_pair_orig_idx[i].begin(),
					this->_pair_orig_idx[i].end());
				tmp.insert(tmp.end(), this->_pair_orig_idx[i + 1].begin(),
					this->_pair_orig_idx[i + 1].end());
			}
			else
			{
				this->_pair_orig_idx[i + 1][0].defeated_orig_idx.push_back(this->_pair_orig_idx[i][0].original_idx);
				d_tmp.value = this->_input_arr[this->_pair_orig_idx[i + 1][0].original_idx].value;
				d_tmp.original_idx = this->_pair_orig_idx[i + 1][0].original_idx;
				d_tmp.defeated_orig_idx = this->_pair_orig_idx[i + 1][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_pair_orig_idx[i + 1].begin(),
					this->_pair_orig_idx[i + 1].end());
				tmp.insert(tmp.end(), this->_pair_orig_idx[i].begin(),
					this->_pair_orig_idx[i].end());
			}
			arr.push_back(tmp);
		}
		else
		{
			// TODO: okasii
			for (size_t j = 0; j < this->_pair_orig_idx[i].size(); ++j)
			{
				data d_tmp;
				// std::cout << "j = " << j << std::endl;
				// std::cout << "orig idx: " <<  this->_pair_orig_idx[i][j].original_idx;
				// std::cout << ", value: " << this->_input_arr[this->_pair_orig_idx[i][j].original_idx].value << std::endl;;
				d_tmp.original_idx = this->_pair_orig_idx[i][j].original_idx;
				d_tmp.value = this->_input_arr[this->_pair_orig_idx[i][j].original_idx].value;
				// straggler.push_back(this->_pair_orig_idx[i][j]);
				straggler.push_back(d_tmp);
			}
		}
		i += 2;
	}

	this->_pair_orig_idx.clear();

	for (size_t i = 0; i < arr.size(); ++i)
	{
		this->_pair_orig_idx.push_back(arr[i]);
	}
	return (straggler);
}

std::vector<size_t> PmergeMe::makeJacobsthalOrder(size_t loser_len)
{
	std::vector<size_t> arr;
	size_t num = 0;
	size_t i = 2;

	arr.push_back(2); // 0
	if (loser_len < 2)
	{
		std::cout << "EEE" << std::endl;
		return (arr);
	}
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

int PmergeMe::binarySearch(int key)
{
	int ng = -1;
	int ok = (int)this->_pair_orig_idx.size();

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
	std::cout << this->_input_arr[this->_pair_orig_idx[index][0].original_idx].value << " vs " << key << std::endl;
	if (this->_input_arr[this->_pair_orig_idx[index][0].original_idx].value >= key)
		return (true);
	return (false);
}

void PmergeMe::printArrAfterSorting(void)
{
	for (size_t i = 0; i < this->_pair_orig_idx.size(); ++i)
	{
		std::cout << this->_input_arr[this->_pair_orig_idx[i][0].original_idx].value << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printArrBeforeSorting(void)
{
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		std::cout << this->_input_arr[i].value << " ";
	}
	std::cout << std::endl;
}

const std::vector<data> PmergeMe::getArr() const
{
	return (this->_input_arr);
}

const std::vector<data> PmergeMe::getSorted() const
{
	return (this->_sorted_vec);
}

const std::vector<std::vector<data> > PmergeMe::getPairOrigIdx() const
{
	return (this->_pair_orig_idx);
}

int PmergeMe::getIndexFromVector(size_t src_orig_idx, std::vector<std::vector<data> > dist)
{
	// TODO: searching loser pair from winner's defeated
	for (size_t i = 0; i < dist.size(); ++i)
	{
		for (size_t j = 0; j < dist[i].size(); ++j)
		{
			for (size_t k = 0; k < dist[i][j].defeated_orig_idx.size(); ++k)
			{
				std::cout << "src idx = " << src_orig_idx
					<< ", dist[" << i << "][" << j << "] = " << dist[i][j].original_idx
					<< "defeated_orig[" << k << "] = " << dist[i][j].defeated_orig_idx[k] << std::endl;
				if (src_orig_idx == dist[i][j].defeated_orig_idx[k])
					return (i);
			}
		}
	}
	return (-1);
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

std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec)
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
