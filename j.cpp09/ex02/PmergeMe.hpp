#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <iterator>
#include <deque>

class PmergeMe
{
private:
	std::vector<int> _arr; // input
	std::vector<int> _main; // winner
	std::vector<int> _pending; // loser
	int _straggler; // extra element
	std::vector<int> _sortedVec; // sorted winner(_main)
	std::deque<int> _sortedDeq; // sorted winner(_main)
	std::vector<int> _order; // inserting order for loser(_pending)
	std::map<int, int> _pendingToMain; // pair with winner and loser  

public:
	PmergeMe(const char **av);
	PmergeMe(const PmergeMe &copy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);

	// funcs
	const std::vector<int> getArr() const;
	const std::vector<int> getSorted() const;
	bool isValidArgs(const char **av);
	void dividePendingIntoMain(std::vector<int> arr);
	void recursiveSort(std::vector<int> arr);
	int binarySearch(int key);
	void mergePendingToMain(void);
	bool isOK(int index, int key);
	std::vector<int> generateJacobsthal(int size);
	void createInsertionOrder(std::vector<int> jacob);
	int findPendingPair(int pending);
	int searchPositionFromSorted(int mainValue);
	int limitedBinarySearch(size_t len, int key);
	size_t getSearchLength(int sortedValue);

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
	void printArr(std::vector<int> vec, std::string msg);
};

// operator
std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);

#endif
