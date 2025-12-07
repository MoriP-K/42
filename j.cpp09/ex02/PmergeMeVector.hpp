#ifndef PMERGEMEVECTOR_HPP
#define PMERGEMEVECTOR_HPP

#include "PmergeMe.hpp"

class PmergeMeVector
{
private:
	std::vector<data> _input_arr;
	std::vector<std::vector<data> > _data;

	size_t _count;

	PmergeMeVector(const PmergeMeVector &copy);
	PmergeMeVector &operator=(const PmergeMeVector &src);

public:
	PmergeMeVector(const char **av);
	~PmergeMeVector();

	bool isValidArgs(const char **av);
	void initArr(void);
	void startSorting(void);
	std::vector<data> comparePair(void);

	std::vector<size_t> makeJacobsthalOrder(size_t tmp_len);
	std::vector<size_t> generateInsertOrder(std::vector<size_t> jacob, size_t tmp_len);

	bool isOK(int index, size_t key);
	int binarySearch(int key);
	size_t limitedBinarySearch(size_t search_limit, size_t search_value);
	int getIndexFromVector(size_t src_orig_idx, std::vector<std::vector<data> > dist);

	const std::vector<data>& getArr() const;
	const std::vector<std::vector<data> >& getPairOrigIdx() const;
	const size_t& getCount() const;
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

#endif
