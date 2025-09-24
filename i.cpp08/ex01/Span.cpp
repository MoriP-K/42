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
	int min;

	if (this->_numbers.size() < 2)
		throw NotEnoughNumberException();
	for (unsigned int i = 0; i < this->_numbers.size(); i++)
	{
		for (unsigned int j = 0; j < this->_numbers.size(); j++)
		{
			if (i == j)
				continue;
			int tmp = 0;
			if (this->_numbers[i] < this->_numbers[j])
				tmp = this->_numbers[j] - this->_numbers[i];
			else
				tmp = this->_numbers[i] - this->_numbers[j];
			if (i == 0 && j == 1)
				min = tmp;
			if (min > tmp)
				min = tmp;
		}
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
