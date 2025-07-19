#ifndef CAT_HPP
#define CAT_HPP

#include "Cat.hpp"

Cat::Cat()
{
}

Cat::Cat(const Cat& copy)
{
	*this = copy;
}

Cat::~Cat()
{
}

Cat &Cat::operator=(const Cat &src)
{
	if (this != &src)
		*this = src;
	return (*this);
}

std::string Cat::getType(void)
{
	return (this->type);
}

#endif
