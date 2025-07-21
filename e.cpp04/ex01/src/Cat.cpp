#include "../inc/Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat: Default Constructor called" << std::endl;
}

Cat::Cat(const Cat& copy)
{
	std::cout << "Cat: Copy Constructor called" << std::endl;
	*this = copy;
}

Cat::~Cat()
{
	std::cout << "Cat: Destructor for " << this->_type <<" called" << std::endl;
}

Cat &Cat::operator=(const Cat &src)
{
	if (this != &src)
	{
		this->_type = src._type;
		*this = src;
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << this->_type << ": Meovv!!" << std::endl;
}
