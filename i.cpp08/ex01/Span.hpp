#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>

class Span
{
private:
	unsigned _N;
	std::vector<int> _numbers;

public:
	Span();
	Span(unsigned int n);
	Span(const Span &copy);
	~Span();
	Span &operator=(const Span &src);

	void addNumber(int n);
	int shortestSpan();
	int longestSpan();

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
