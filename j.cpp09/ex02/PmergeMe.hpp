#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

struct data
{
	size_t value;
	size_t original_idx;
	std::vector<size_t> defeated_orig_idx;

	data() : value(0), original_idx(0) {}
	data(size_t v, size_t idx) : value(v), original_idx(idx) {}
};

// operator
std::ostream &operator<<(std::ostream &out, const data &d);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &d);
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec);
std::ostream &operator<<(std::ostream &out, const std::deque<int> &deq);
std::ostream &operator<<(std::ostream &out, const std::deque<data> &deq);


#endif
