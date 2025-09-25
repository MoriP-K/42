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

const std::vector<int> &Span::getNumbers(void) const
{
	return (this->_numbers);
}

void Span::addNumber(int n)
{
	if (this->_numbers.size() >= this->_N)
		throw FullContainerException();
	this->_numbers.push_back(n);
}

int Span::shortestSpan(void)
{
	if (this->_numbers.size() < 2)
		throw NotEnoughNumberException();

	std::vector<int> sorted = this->_numbers;
	std::sort(sorted.begin(), sorted.end());

	int min = sorted[1] - sorted[0];

	for (unsigned int i = 2; i < sorted.size(); i++)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < min)
			min = diff;
	}
	return (min);
}

int Span::longestSpan(void)
{
	int max;
	int min;
	int res;

	if (this->_numbers.size() < 2)
		throw NotEnoughNumberException();
	for (unsigned int i = 0; i < this->_numbers.size(); i++)
	{
		if (i == 0)
		{
			max = this->_numbers[i];
			min = this->_numbers[i];
			continue;
		}
		if (max < this->_numbers[i])
			max = this->_numbers[i];
		if (min > this->_numbers[i])
			min = this->_numbers[i];
	}
	res = max - min;
	return (res);
}

const char* Span::FullContainerException::what() const throw()
{
	return ("Container is full.");
}

const char* Span::NotEnoughNumberException::what() const throw()
{
	return ("Not enough numbers in container.");
}
