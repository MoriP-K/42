#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <iterator>
#include <deque>
#include <ctime>
#include <iomanip>
#include <sys/time.h>

class PmergeMe
{
private:
	std::vector<size_t> _arr; // input
	std::vector<size_t> _sorted_vec; // sorted winner(_main)
	std::deque<size_t> _sorted_deq; // sorted winner(_main)
	size_t _count; // delete

public:
	PmergeMe(const char **av);
	PmergeMe(const PmergeMe &copy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);

	// funcs
	const std::vector<size_t> getArr() const;
	const std::vector<size_t> getSorted() const;

	bool isValidArgs(const char **av);
	int binarySearch(int key);
	bool isOK(int index, size_t key);
	std::vector<int> generateJacobsthal(int size);
	std::vector<int> createInsertionOrder(std::vector<int> jacob, size_t pending_len);
	int limitedBinarySearch(size_t len, size_t key);

	void MIS(std::vector<size_t> arr);

	// void MergeInsertionSort(std::vector<size_t> chain, int depth);
	void testMIS(std::vector<size_t> arr);

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

// operator
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &vec);

#endif
