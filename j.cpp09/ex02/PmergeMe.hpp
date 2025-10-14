#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <cstdlib>

class PmergeMe
{
private:
	std::vector<int> _arr;
	std::vector<int> _main;
	std::vector<int> _sorted;
	std::map<int, int> _pair;

public:
	PmergeMe(const char **av);
	PmergeMe(const PmergeMe &copy);
	~PmergeMe();
	PmergeMe &operator=(const PmergeMe &src);

	class ErrorException: public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Error");
		}
	};

	const std::vector<int> getArr() const;
	const std::vector<int> getSorted() const;
	bool isValidArgs(const char **av);
	void comparePair(std::vector<int> arr);
	int binarySearch(int key);
	bool isOK(int index, int ket);
	std::vector<int> generateJacobsthal(size_t size);

	void printArr(std::vector<int> vec, std::string msg);

};

std::ostream &operator<<(std::ostream &out, const std::vector<int> &vec);


#endif
