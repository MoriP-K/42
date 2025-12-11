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

class PmergeMe
{
private:
	// vector
	std::vector<data> _input_arr_vec;
	std::vector<std::vector<data> > _data_vec;
	size_t _count_vec;

	// deque
	std::deque<data> _input_arr_deq;
	std::vector<std::deque<data> > _data_deq;
	size_t _count_deq;

	PmergeMe(const PmergeMe &copy);
	PmergeMe &operator=(const PmergeMe &src);

public:
	PmergeMe(const char **av);
	~PmergeMe();

	// vector
	bool isValidArgsVec(const char **av);
	void initArrVec(void);
	void startSortingVec(void);
	std::vector<data> comparePairVec(void);
	std::vector<size_t> makeJacobsthalOrderVec(size_t tmp_len);
	std::vector<size_t> generateInsertOrderVec(std::vector<size_t> jacob, size_t tmp_len);
	bool isOKVec(int index, size_t key);
	int binarySearchVec(int key);
	size_t limitedBinarySearchVec(size_t search_limit, size_t search_value);
	int getIndexFromVectorVec(size_t src_orig_idx, std::vector<std::vector<data> > dist);

	const std::vector<data>& getArrVec() const;
	const std::vector<std::vector<data> >& getPairOrigIdxVec() const;
	const size_t& getCountVec() const;
	size_t arrSizeVec(void) const;

	// deque
	bool isValidArgsDeq(const char **av);
	void initArrDeq(void);
	void startSortingDeq(void);
	std::deque<data> comparePairDeq(void);
	std::vector<size_t> makeJacobsthalOrderDeq(size_t tmp_len);
	std::vector<size_t> generateInsertOrderDeq(std::vector<size_t> jacob, size_t tmp_len);
	bool isOKDeq(int index, size_t key);
	int binarySearchDeq(int key);
	size_t limitedBinarySearchDeq(size_t search_limit, size_t search_value);
	int getIndexFromVectorDeq(size_t src_orig_idx, std::vector<std::deque<data> > dist);

	const std::deque<data>& getArrDeq() const;
	const std::vector<std::deque<data> >& getPairOrigIdxDeq() const;
	const size_t& getCountDeq() const;
	size_t arrSizeDeq(void) const;

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
	void printArrBeforeSortingVec(void);
	void printArrAfterSortingVec(void);
	void printArrWIPVec(void);

	void printArrBeforeSortingDeq(void);
	void printArrAfterSortingDeq(void);
	void printArrWIPDeq(void);
};
// operator
std::ostream &operator<<(std::ostream &out, const data &d);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &d);
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec);
std::ostream &operator<<(std::ostream &out, const std::deque<int> &deq);
std::ostream &operator<<(std::ostream &out, const std::deque<data> &deq);


#endif
