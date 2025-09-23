#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>

class NotFoundExecption: public std::exception
{
public:
	virtual const char *what() const throw()
	{
		return ("Number not found.");
	}
};

template <typename T>
typename T::iterator easyfind(T &container, int n)
{
	typename T::iterator it;

	it = std::find(container.begin(), container.end(), n);
	if (it == container.end())
		throw NotFoundExecption();
	return (it);
}

#endif
