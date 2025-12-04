#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <deque>
#include <iterator>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string RESET = "\033[0m";
const std::string YELLOW = "\033[33m";
const std::string WHITE = "\033[37m";

struct data
{
	size_t value;
	size_t original_idx;
	std::vector<size_t> defeated_orig_idx;

	data() : value(0), original_idx(0) {}
	data(size_t v, size_t idx) : value(v), original_idx(idx) {}
};

template <typename Container>
class PmergeMe
{
private:
	Container _input_arr;
	std::vector<Container> _data_vec;

	size_t _count;

	PmergeMe(const PmergeMe &copy);
	PmergeMe &operator=(const PmergeMe &src);

public:
	PmergeMe(const char **av);
	~PmergeMe();

	bool isValidArgs(const char **av);
	void initArr(void);
	void startSorting(void);
	Container comparePair(void);

	std::vector<size_t> makeJacobsthalOrder(size_t tmp_len);
	std::vector<size_t> generateInsertOrder(std::vector<size_t> jacob, size_t tmp_len);

	bool isOK(int index, size_t key);
	int binarySearch(int key);
	size_t limitedBinarySearch(size_t search_limit, size_t search_value);
	int getIndexFromVector(size_t src_orig_idx, std::vector<Container> dist);

	const Container& getArr() const;
	const std::vector<Container>& getPairOrigIdx() const;
	size_t arrSize(void) const;

	// exception
	class ErrorException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error");
		}
	};

	// DEBUG
	void printArrBeforeSorting(void);
	void printArrAfterSorting(void);
	void printArrWIP(void);
};

void invalidArgument(void);

// operator
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec);
std::ostream &operator<<(std::ostream &out, const data &vec);

#include "PmergeMe.tpp"

#endif
