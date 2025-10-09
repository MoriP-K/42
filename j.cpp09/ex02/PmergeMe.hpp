#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <iostream>
#include <iterator>
#include <cstdlib>

class PmergeMe
{
private:
	std::vector<int> _arr;
	std::vector<int> _main;
	// std::vector<int> _pending;
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
	bool isValidArgs(const char **av);
	void comparePair(std::vector<int> bigger);

	void printArr(std::vector<int> vec, std::string msg);

};

#endif
