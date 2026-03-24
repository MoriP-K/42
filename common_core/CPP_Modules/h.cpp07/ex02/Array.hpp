#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <exception>
#include <cstdlib>

template <typename T>
class Array
{
private:
	T	*_arr;
	unsigned int	_size;

public:
	Array();
	Array(unsigned int n);
	Array(Array const &copy);
	~Array();

	Array &operator=(Array const &src);
	T &operator[](unsigned int i);
	T const &operator[](unsigned int i) const;

	unsigned int size() const;

	class OutOfBoundsException: public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};

#include "Array.tpp"

#endif
