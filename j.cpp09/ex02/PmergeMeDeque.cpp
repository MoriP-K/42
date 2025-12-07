#include "PmergeMeDeque.hpp"

PmergeMeDeque::PmergeMeDeque(const char **av)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	this->_count = 0;
}

PmergeMeDeque::PmergeMeDeque(const PmergeMeDeque &copy)
	: _input_arr(copy._input_arr), _data(copy._data), _count(copy._count)
{
}

PmergeMeDeque::~PmergeMeDeque()
{
}

PmergeMeDeque &PmergeMeDeque::operator=(const PmergeMeDeque &src)
{
	if (this != &src)
	{
		this->_input_arr = src._input_arr;
		this->_data = src._data;
		this->_count = src._count;
	}
	return (*this);
}

bool PmergeMeDeque::isValidArgs(const char **av)
{
	long num = 0;

	for (size_t i = 1; av[i]; ++i)
	{
		if (av[i][0] == '\0')
			return (false);
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

void PmergeMeDeque::initArr()
{
	for (size_t i = 0; i < this->_input_arr.size(); ++i)
	{
		std::deque<data> tmp;
		data d_tmp;
		d_tmp.original_idx = i;
		tmp.push_back(d_tmp);
		this->_data.push_back(tmp);
	}
}

void PmergeMeDeque::startSorting(void)
{
	std::deque<data> straggler_idx;

	if (this->_data.size() == 1)
		return ;

	static size_t depth = 0;

	depth++;
	straggler_idx = comparePair();
	this->startSorting();
	depth--;

	std::vector<std::deque<data> > tmp;
	size_t pair_count = 0;
	for (size_t i = 0; i < this->_data.size(); ++i)
	{
		size_t center_idx = this->_data[i].size() / 2;
		std::deque<data> vec;

		for (size_t j = center_idx; j < this->_data[i].size(); ++j)
		{
			data d_tmp;
			d_tmp.original_idx = this->_data[i][j].original_idx;
			d_tmp.defeated_orig_idx = this->_data[i][j].defeated_orig_idx;
			d_tmp.value = this->_data[i][j].value;
			vec.push_back(d_tmp);
		}
		tmp.push_back(vec);
		++pair_count;
		this->_data[i].erase(this->_data[i].begin() + center_idx, this->_data[i].end());
	}
	if (!straggler_idx.empty())
		tmp.push_back(straggler_idx);

	std::vector<size_t> jacob = makeJacobsthalOrder(tmp.size());
	std::vector<size_t> order = generateInsertOrder(jacob, tmp.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		int insert_pos = 0;

		if (idx == 0)
		{
			this->_data.insert(this->_data.begin(), tmp[idx]);
			tmp[idx].clear();
			continue;
		}
		if (idx < pair_count)
		{
			int search_limit = getIndexFromVector(tmp[idx][0].original_idx, this->_data);
			if (search_limit == -1)
				return ;
			insert_pos = limitedBinarySearch(search_limit, this->_input_arr[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		else
		{
			insert_pos = binarySearch(this->_input_arr[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		this->_data.insert(this->_data.begin() + insert_pos, tmp[idx]);
		tmp[idx].clear();
	}
}

std::deque<data> PmergeMeDeque::comparePair(void)
{
	std::vector<std::deque<data> > arr;
	std::deque<data> straggler;

	for (size_t i = 0; i < this->_data.size();)
	{
		if (i + 1 < this->_data.size())
		{
			std::deque<data> tmp;
			data d_tmp;
			++this->_count;

			if (this->_input_arr[this->_data[i][0].original_idx].value
				> this->_input_arr[this->_data[i + 1][0].original_idx].value)
			{
				this->_data[i][0].defeated_orig_idx.push_back(this->_data[i + 1][0].original_idx);
				d_tmp.value = this->_input_arr[this->_data[i][0].original_idx].value;
				d_tmp.original_idx = this->_data[i][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data[i][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data[i].begin(),
					this->_data[i].end());
				tmp.insert(tmp.end(), this->_data[i + 1].begin(),
					this->_data[i + 1].end());
			}
			else
			{
				this->_data[i + 1][0].defeated_orig_idx.push_back(this->_data[i][0].original_idx);
				d_tmp.value = this->_input_arr[this->_data[i + 1][0].original_idx].value;
				d_tmp.original_idx = this->_data[i + 1][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data[i + 1][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data[i + 1].begin(),
					this->_data[i + 1].end());
				tmp.insert(tmp.end(), this->_data[i].begin(),
					this->_data[i].end());
			}
			arr.push_back(tmp);
		}
		else
		{
			for (size_t j = 0; j < this->_data[i].size(); ++j)
			{
				data d_tmp;
				d_tmp.original_idx = this->_data[i][j].original_idx;
				d_tmp.value = this->_input_arr[this->_data[i][j].original_idx].value;
				d_tmp.defeated_orig_idx = this->_data[i][j].defeated_orig_idx;
				straggler.push_back(d_tmp);
			}
		}
		i += 2;
	}

	this->_data.clear();

	for (size_t i = 0; i < arr.size(); ++i)
		this->_data.push_back(arr[i]);

	return (straggler);
}

std::vector<size_t> PmergeMeDeque::makeJacobsthalOrder(size_t tmp_len)
{
	std::vector<size_t> arr;
	size_t num = 0;
	size_t i = 2;

	arr.push_back(2);
	if (tmp_len < 2)
		return (arr);

	arr.push_back(2);
	while (1)
	{
		num = arr[i - 1] + arr[i - 2] * 2;
		if (num < tmp_len)
			arr.push_back(num);
		else
			break;
		++i;
	}
	return (arr);
}

std::vector<size_t> PmergeMeDeque::generateInsertOrder(std::vector<size_t> jacob, size_t tmp_len)
{
	std::vector<size_t> order;

	order.push_back(0);
	if (tmp_len < 2)
		return (order);

	if (tmp_len == 2)
	{
		order.push_back(1);
		return (order);
	}

	size_t value = 1;
	for (size_t i = 1; i < jacob.size() && order.size() + jacob[i - 1] <= tmp_len; ++i)
	{
		std::vector<size_t> num;
		num.clear();
		for (size_t j = jacob[i - 1]; 0 < j; --j)
		{
			num.push_back(value);
			++value;
		}
		while (0 < num.size())
		{
			order.push_back(num.back());
			num.pop_back();
		}
	}

	for (size_t i = tmp_len - 1; i >= value; --i)
	{
		order.push_back(i);
		if (i == 0)
			break;
	}
	return (order);
}

size_t PmergeMeDeque::limitedBinarySearch(size_t search_limit, size_t search_value)
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

int PmergeMeDeque::binarySearch(int key)
{
	int ng = -1;
	int ok = (int)this->_data.size();

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

int PmergeMeDeque::getIndexFromVector(size_t src_orig_idx, std::vector<std::deque<data> > dist)
{
	for (size_t i = 0; i < dist.size(); ++i)
	{
		for (size_t j = 0; j < dist[i].size(); ++j)
		{
			for (size_t k = 0; k < dist[i][j].defeated_orig_idx.size(); ++k)
			{
				if (src_orig_idx == dist[i][j].defeated_orig_idx[k])
					return (i);
			}
		}
	}
	return (-1);
}

bool PmergeMeDeque::isOK(int index, size_t key)
{
	++this->_count;
	if (this->_input_arr[this->_data[index][0].original_idx].value >= key)
		return (true);
	return (false);
}

const std::deque<data>& PmergeMeDeque::getArr() const
{
	return (this->_input_arr);
}

const std::vector<std::deque<data> >& PmergeMeDeque::getPairOrigIdx() const
{
	return (this->_data);
}

const size_t& PmergeMeDeque::getCount() const
{
	return (this->_count);
}

size_t PmergeMeDeque::arrSize(void) const
{
	return (this->_input_arr.size());
}

void PmergeMeDeque::printArrBeforeSorting(void)
{
	if (this->_input_arr.size() < 6)
	{
		for (size_t i = 0; i < this->_input_arr.size(); ++i)
		{
			std::cout << this->_input_arr[i].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr[i].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

void PmergeMeDeque::printArrAfterSorting(void)
{
	if (this->_data.size() < 6)
	{
		for (size_t i = 0; i < this->_data.size(); ++i)
		{
			std::cout << this->_input_arr[this->_data[i][0].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr[this->_data[i][0].original_idx].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

void PmergeMeDeque::printArrWIP(void)
{
	std::cout << "--- WIP ---" << std::endl;
	for (size_t i = 0; i < this->_data.size(); ++i)
	{
		std::cout << "[" << i << "]\n";
		for (size_t j = 0; j < this->_data[i].size(); ++j)
		{
			std::cout << "[" << j << "]";
			std::cout << this->_input_arr[this->_data[i][j].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
