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

struct data
{
	size_t original_idx;
	size_t value;
	std::vector<size_t> defeated_idx;
};

class PmergeMe
{
private:
	std::vector<size_t> _input_arr; // input
	std::vector<data> _sorted_vec; // sorted winner(_main)
	std::deque<size_t> _sorted_deq; // sorted winner(_main)
	std::vector<data> _info;

	size_t _count; // delete

public:
	PmergeMe(const char **av);
	PmergeMe(const PmergeMe &copy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);

	bool isValidArgs(const char **av);
	void initData(void);

	void startSorting(std::vector<data> info);
	std::vector<size_t> makeJacobsthalOrder(size_t loser_len);
	std::vector<size_t> generateInsertOrder(std::vector<size_t> jacob, size_t loser_len);

	int binarySearch(int key);
	bool isOK(int index, size_t key);

	const std::vector<size_t> getArr() const;
	const std::vector<data> getSorted() const;

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
};

void invalidArgument(void);
// operator
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<data> &vec);

#endif
