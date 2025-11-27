#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <map>
#include <vector>
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

class PmergeMe
{
private:
	std::vector<data> _input_arr; // input
	std::vector<data> _sorted_vec; // sorted winner(_main)
	std::vector<std::vector<data > > _pair_orig_idx;
	std::deque<data> _sorted_deq; // sorted winner(_main)
	std::vector<data> _info;

	size_t _count; // delete
	size_t _total; // delete

public:
	PmergeMe(const char **av);
	PmergeMe(const PmergeMe &copy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);

	bool isValidArgs(const char **av);
	void initArr(void);

	void startSorting(void);
	std::vector<data> comparePair(void);
	std::vector<size_t> makeJacobsthalOrder(size_t loser_len);
	std::vector<size_t> generateInsertOrder(std::vector<size_t> jacob, size_t loser_len);
	int binarySearch(int key);
	bool isOK(int index, size_t key);
	size_t limitedBinarySearch(size_t search_limit, size_t search_value);

	const std::vector<data> getArr() const;
	const std::vector<data> getSorted() const;
	const std::vector<std::vector<data> > getPairOrigIdx() const;
	int getIndexFromVector(size_t src_orig_idx, std::vector<std::vector<data> > dist);

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
	size_t arrSize(void);
	void printArr(std::vector<size_t> vec, std::string msg);
	void printCount(void);
	void printNow(std::vector<data> winner, std::vector<data> loser);
	void printInfo(std::vector<std::vector<size_t> > arr, const std::string& color);
	void printArrBeforeSorting(void);
	void printArrAfterSorting(void);
};

void invalidArgument(void);
// operator
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec);
std::ostream &operator<<(std::ostream &out, const data &vec);

#endif
