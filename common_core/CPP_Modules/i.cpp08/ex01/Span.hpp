#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

class Span
{
private:
	unsigned int _N;
	std::vector<int> _numbers;

public:
	Span();
	Span(unsigned int n);
	Span(const Span &copy);
	~Span();
	Span &operator=(const Span &src);

	const std::vector<int> &getNumbers(void) const;
	void addNumber(int n);
	int shortestSpan(void);
	int longestSpan(void);
	template <typename Iterator>
	void addRange(Iterator begin, Iterator end)
	{
		unsigned int distance = std::distance(begin, end);
		if (this->_numbers.size() + distance > this->_N)
			throw FullContainerException();
		for (Iterator it = begin; it != end; ++it)
			this->_numbers.push_back(*it);
	}

	class FullContainerException: public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class NotEnoughNumberException: public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
