#include "PmergeMe.hpp"

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
