#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const char **av) : _count_vec(0), _count_deq(0)
{
	if (!this->isValidArgs(av))
		throw ErrorException();
	for (size_t i = 0; i < this->_input_arr_vec.size(); ++i)
	{
		data tmp;
		tmp.value = this->_input_arr_vec[i].value;
		this->_input_arr_deq.push_back(tmp);
	}
}

PmergeMe::~PmergeMe()
{
}

//  ===================================  vector  =================================== //
bool PmergeMe::isValidArgs(const char **av)
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
		this->_input_arr_vec.push_back(tmp);
	}
	return (true);
}

void PmergeMe::initArrVec(void)
{
	for (size_t i = 0; i < this->_input_arr_vec.size(); ++i)
	{
		std::vector<data> tmp;
		data d_tmp;
		d_tmp.original_idx = i;
		tmp.push_back(d_tmp);
		this->_data_vec.push_back(tmp);
	}
}

void PmergeMe::startSortingVec(void)
{
	std::vector<data> straggler_idx;

	if (this->_data_vec.size() == 1)
		return ;

	static size_t depth = 0;

	depth++;
	straggler_idx = comparePairVec();
	this->startSortingVec();
	depth--;

	std::vector<std::vector<data> > tmp;
	size_t pair_count = 0;
	for (size_t i = 0; i < this->_data_vec.size(); ++i)
	{
		size_t center_idx = this->_data_vec[i].size() / 2;
		std::vector<data> vec;

		for (size_t j = center_idx; j < this->_data_vec[i].size(); ++j)
		{
			data d_tmp;
			d_tmp.original_idx = this->_data_vec[i][j].original_idx;
			d_tmp.defeated_orig_idx = this->_data_vec[i][j].defeated_orig_idx;
			d_tmp.value = this->_data_vec[i][j].value;
			vec.push_back(d_tmp);
		}
		tmp.push_back(vec);
		++pair_count;
		this->_data_vec[i].erase(this->_data_vec[i].begin() + center_idx, this->_data_vec[i].end());
	}
	if (!straggler_idx.empty())
		tmp.push_back(straggler_idx);

	std::vector<size_t> jacob = makeJacobsthalOrderVec(tmp.size());
	std::vector<size_t> order = generateInsertOrderVec(jacob, tmp.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		int insert_pos = 0;

		if (idx == 0)
		{
			this->_data_vec.insert(this->_data_vec.begin(), tmp[idx]);
			tmp[idx].clear();
			continue;
		}
		if (idx < pair_count)
		{
			int search_limit = getIndexFromVectorVec(tmp[idx][0].original_idx, this->_data_vec);
			if (search_limit == -1)
				return ;
			insert_pos = limitedBinarySearchVec(search_limit, this->_input_arr_vec[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		else
		{
			insert_pos = binarySearchVec(this->_input_arr_vec[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		this->_data_vec.insert(this->_data_vec.begin() + insert_pos, tmp[idx]);
		tmp[idx].clear();
	}
}

std::vector<data> PmergeMe::comparePairVec(void)
{
	std::vector<std::vector<data> > arr;
	std::vector<data> straggler;

	for (size_t i = 0; i < this->_data_vec.size();)
	{
		if (i + 1 < this->_data_vec.size())
		{
			std::vector<data> tmp;
			data d_tmp;
			++this->_count_vec;

			if (this->_input_arr_vec[this->_data_vec[i][0].original_idx].value
				> this->_input_arr_vec[this->_data_vec[i + 1][0].original_idx].value)
			{
				this->_data_vec[i][0].defeated_orig_idx.push_back(this->_data_vec[i + 1][0].original_idx);
				d_tmp.value = this->_input_arr_vec[this->_data_vec[i][0].original_idx].value;
				d_tmp.original_idx = this->_data_vec[i][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data_vec[i][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data_vec[i].begin(),
					this->_data_vec[i].end());
				tmp.insert(tmp.end(), this->_data_vec[i + 1].begin(),
					this->_data_vec[i + 1].end());
			}
			else
			{
				this->_data_vec[i + 1][0].defeated_orig_idx.push_back(this->_data_vec[i][0].original_idx);
				d_tmp.value = this->_input_arr_vec[this->_data_vec[i + 1][0].original_idx].value;
				d_tmp.original_idx = this->_data_vec[i + 1][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data_vec[i + 1][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data_vec[i + 1].begin(),
					this->_data_vec[i + 1].end());
				tmp.insert(tmp.end(), this->_data_vec[i].begin(),
					this->_data_vec[i].end());
			}
			arr.push_back(tmp);
		}
		else
		{
			for (size_t j = 0; j < this->_data_vec[i].size(); ++j)
			{
				data d_tmp;
				d_tmp.original_idx = this->_data_vec[i][j].original_idx;
				d_tmp.value = this->_input_arr_vec[this->_data_vec[i][j].original_idx].value;
				d_tmp.defeated_orig_idx = this->_data_vec[i][j].defeated_orig_idx;
				straggler.push_back(d_tmp);
			}
		}
		i += 2;
	}

	this->_data_vec.clear();

	for (size_t i = 0; i < arr.size(); ++i)
		this->_data_vec.push_back(arr[i]);

	return (straggler);
}

std::vector<size_t> PmergeMe::makeJacobsthalOrderVec(size_t tmp_len)
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

std::vector<size_t> PmergeMe::generateInsertOrderVec(std::vector<size_t> jacob, size_t tmp_len)
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

size_t PmergeMe::limitedBinarySearchVec(size_t search_limit, size_t search_value)
{
	if (search_limit == 0)
		return (0);

	int ng = -1;
	int ok = search_limit;

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOKVec(mid, search_value))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

int PmergeMe::binarySearchVec(int key)
{
	int ng = -1;
	int ok = (int)this->_data_vec.size();

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOKVec(mid, key))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

int PmergeMe::getIndexFromVectorVec(size_t src_orig_idx, std::vector<std::vector<data> > dist)
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

bool PmergeMe::isOKVec(int index, size_t key)
{
	++this->_count_vec;
	if (this->_input_arr_vec[this->_data_vec[index][0].original_idx].value >= key)
		return (true);
	return (false);
}

const std::vector<data>& PmergeMe::getArrVec() const
{
	return (this->_input_arr_vec);
}

const std::vector<std::vector<data> >& PmergeMe::getPairOrigIdxVec() const
{
	return (this->_data_vec);
}

const size_t& PmergeMe::getCountVec() const
{
	return (this->_count_vec);
}

size_t PmergeMe::arrSizeVec(void) const
{
	return (this->_input_arr_vec.size());
}

void PmergeMe::printArrBeforeSortingVec(void)
{
	if (this->_input_arr_vec.size() < 6)
	{
		for (size_t i = 0; i < this->_input_arr_vec.size(); ++i)
		{
			std::cout << this->_input_arr_vec[i].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr_vec[i].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

void PmergeMe::printArrWIPVec(void)
{
	std::cout << "--- WIP ---" << std::endl;
	for (size_t i = 0; i < this->_data_vec.size(); ++i)
	{
		std::cout << "[" << i << "]\n";
		for (size_t j = 0; j < this->_data_vec[i].size(); ++j)
		{
			std::cout << "[" << j << "]";
			std::cout << this->_input_arr_vec[this->_data_vec[i][j].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

//  ===================================  deque  =================================== //
void PmergeMe::initArrDeq(void)
{
	for (size_t i = 0; i < this->_input_arr_deq.size(); ++i)
	{
		std::deque<data> tmp;
		data d_tmp;
		d_tmp.original_idx = i;
		tmp.push_back(d_tmp);
		this->_data_deq.push_back(tmp);
	}
}

void PmergeMe::startSortingDeq(void)
{
	std::deque<data> straggler_idx;

	if (this->_data_deq.size() == 1)
		return ;

	static size_t depth = 0;

	depth++;
	straggler_idx = comparePairDeq();
	this->startSortingDeq();
	depth--;

	std::vector<std::deque<data> > tmp;
	size_t pair_count = 0;
	for (size_t i = 0; i < this->_data_deq.size(); ++i)
	{
		size_t center_idx = this->_data_deq[i].size() / 2;
		std::deque<data> vec;

		for (size_t j = center_idx; j < this->_data_deq[i].size(); ++j)
		{
			data d_tmp;
			d_tmp.original_idx = this->_data_deq[i][j].original_idx;
			d_tmp.defeated_orig_idx = this->_data_deq[i][j].defeated_orig_idx;
			d_tmp.value = this->_data_deq[i][j].value;
			vec.push_back(d_tmp);
		}
		tmp.push_back(vec);
		++pair_count;
		this->_data_deq[i].erase(this->_data_deq[i].begin() + center_idx, this->_data_deq[i].end());
	}
	if (!straggler_idx.empty())
		tmp.push_back(straggler_idx);

	std::vector<size_t> jacob = makeJacobsthalOrderDeq(tmp.size());
	std::vector<size_t> order = generateInsertOrderDeq(jacob, tmp.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t idx = order[i];
		int insert_pos = 0;

		if (idx == 0)
		{
			this->_data_deq.insert(this->_data_deq.begin(), tmp[idx]);
			tmp[idx].clear();
			continue;
		}
		if (idx < pair_count)
		{
			int search_limit = getIndexFromVectorDeq(tmp[idx][0].original_idx, this->_data_deq);
			if (search_limit == -1)
				return ;
			insert_pos = limitedBinarySearchDeq(search_limit, this->_input_arr_deq[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		else
		{
			insert_pos = binarySearchDeq(this->_input_arr_deq[tmp[idx][0].original_idx].value);
			if (insert_pos == -1)
				return ;
		}
		this->_data_deq.insert(this->_data_deq.begin() + insert_pos, tmp[idx]);
		tmp[idx].clear();
	}
}

std::deque<data> PmergeMe::comparePairDeq(void)
{
	std::vector<std::deque<data> > arr;
	std::deque<data> straggler;

	for (size_t i = 0; i < this->_data_deq.size();)
	{
		if (i + 1 < this->_data_deq.size())
		{
			std::deque<data> tmp;
			data d_tmp;
			++this->_count_deq;

			if (this->_input_arr_deq[this->_data_deq[i][0].original_idx].value
				> this->_input_arr_deq[this->_data_deq[i + 1][0].original_idx].value)
			{
				this->_data_deq[i][0].defeated_orig_idx.push_back(this->_data_deq[i + 1][0].original_idx);
				d_tmp.value = this->_input_arr_deq[this->_data_deq[i][0].original_idx].value;
				d_tmp.original_idx = this->_data_deq[i][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data_deq[i][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data_deq[i].begin(),
					this->_data_deq[i].end());
				tmp.insert(tmp.end(), this->_data_deq[i + 1].begin(),
					this->_data_deq[i + 1].end());
			}
			else
			{
				this->_data_deq[i + 1][0].defeated_orig_idx.push_back(this->_data_deq[i][0].original_idx);
				d_tmp.value = this->_input_arr_deq[this->_data_deq[i + 1][0].original_idx].value;
				d_tmp.original_idx = this->_data_deq[i + 1][0].original_idx;
				d_tmp.defeated_orig_idx = this->_data_deq[i + 1][0].defeated_orig_idx;
				tmp.insert(tmp.end(), this->_data_deq[i + 1].begin(),
					this->_data_deq[i + 1].end());
				tmp.insert(tmp.end(), this->_data_deq[i].begin(),
					this->_data_deq[i].end());
			}
			arr.push_back(tmp);
		}
		else
		{
			for (size_t j = 0; j < this->_data_deq[i].size(); ++j)
			{
				data d_tmp;
				d_tmp.original_idx = this->_data_deq[i][j].original_idx;
				d_tmp.value = this->_input_arr_deq[this->_data_deq[i][j].original_idx].value;
				d_tmp.defeated_orig_idx = this->_data_deq[i][j].defeated_orig_idx;
				straggler.push_back(d_tmp);
			}
		}
		i += 2;
	}

	this->_data_deq.clear();

	for (size_t i = 0; i < arr.size(); ++i)
		this->_data_deq.push_back(arr[i]);

	return (straggler);
}

std::vector<size_t> PmergeMe::makeJacobsthalOrderDeq(size_t tmp_len)
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

std::vector<size_t> PmergeMe::generateInsertOrderDeq(std::vector<size_t> jacob, size_t tmp_len)
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

size_t PmergeMe::limitedBinarySearchDeq(size_t search_limit, size_t search_value)
{
	if (search_limit == 0)
		return (0);

	int ng = -1;
	int ok = search_limit;

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOKDeq(mid, search_value))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

int PmergeMe::binarySearchDeq(int key)
{
	int ng = -1;
	int ok = (int)this->_data_deq.size();

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOKDeq(mid, key))
			ok = mid;
		else
			ng = mid;
	}
	return (ok);
}

int PmergeMe::getIndexFromVectorDeq(size_t src_orig_idx, std::vector<std::deque<data> > dist)
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

bool PmergeMe::isOKDeq(int index, size_t key)
{
	++this->_count_deq;
	if (this->_input_arr_deq[this->_data_deq[index][0].original_idx].value >= key)
		return (true);
	return (false);
}

const std::deque<data>& PmergeMe::getArrDeq() const
{
	return (this->_input_arr_deq);
}

const std::vector<std::deque<data> >& PmergeMe::getPairOrigIdxDeq() const
{
	return (this->_data_deq);
}

const size_t& PmergeMe::getCountDeq() const
{
	return (this->_count_deq);
}

size_t PmergeMe::arrSizeDeq(void) const
{
	return (this->_input_arr_deq.size());
}

void PmergeMe::printArrBeforeSortingDeq(void)
{
	if (this->_input_arr_deq.size() < 6)
	{
		for (size_t i = 0; i < this->_input_arr_deq.size(); ++i)
		{
			std::cout << this->_input_arr_deq[i].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr_deq[i].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

void PmergeMe::printArrWIPDeq(void)
{
	std::cout << "--- WIP ---" << std::endl;
	for (size_t i = 0; i < this->_data_deq.size(); ++i)
	{
		std::cout << "[" << i << "]\n";
		for (size_t j = 0; j < this->_data_deq[i].size(); ++j)
		{
			std::cout << "[" << j << "]";
			std::cout << this->_input_arr_deq[this->_data_deq[i][j].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void PmergeMe::printArrAfterSortingVec(void)
{
	if (this->_data_vec.size() < 6)
	{
		for (size_t i = 0; i < this->_data_vec.size(); ++i)
		{
			std::cout << this->_input_arr_vec[this->_data_vec[i][0].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr_vec[this->_data_vec[i][0].original_idx].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

void PmergeMe::printArrAfterSortingDeq(void)
{
	if (this->_data_deq.size() < 6)
	{
		for (size_t i = 0; i < this->_data_deq.size(); ++i)
		{
			std::cout << this->_input_arr_deq[this->_data_deq[i][0].original_idx].value << " ";
		}
		std::cout << std::endl;
	}
	else
	{
		for (size_t i = 0; i < 5; ++i)
		{
			std::cout << this->_input_arr_deq[this->_data_deq[i][0].original_idx].value << " ";
		}
		std::cout << "[...]";
		std::cout << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, const data &d)
{
	out << "value: " << d.value << ", orig idx: " << d.original_idx;
	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &d)
{
	for (size_t i = 0; i < d.size(); ++i)
		out << d[i] << " ";
	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec)
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

std::ostream &operator<<(std::ostream &out, const std::deque<int> &deq)
{
	for (size_t i = 0; i < deq.size(); ++i)
		out << deq[i] << " ";
	return (out);
}


std::ostream &operator<<(std::ostream &out, const std::deque<data> &deq)
{
	for (size_t i = 0; i < deq.size(); ++i)
		out << deq[i] << " ";
	return (out);
}
