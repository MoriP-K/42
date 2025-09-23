#include "Span.hpp"

Span::Span(): _N(0)
{
}

Span::Span(unsigned int n): _N(n)
{
}

Span::Span(const Span &copy)
{
	*this = copy;
}

Span::~Span()
{
}

Span &Span::operator=(const Span &src)
{
	if (this != &src)
	{
		this->_N = src._N;
		this->_numbers = src._numbers;
	}
	return (*this);
}

void Span::addNumber(int n)
{
	if (this->_numbers.size() >= this->_N)
		throw FullContainerException();
	this->_numbers.push_back(n);
}
int Span::shortestSpan()
{
	return (this->_N);
}

int Span::longestSpan()
{
	return (this->_N);
}

const char* Span::FullContainerException::what() const throw()
{
	return ("Container is full.");
}

const char* Span::NotEnoughNumberException::what() const throw()
{
	return ("Not enough numbers in container.");
}
