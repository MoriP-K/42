#include "../inc/Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat: Default Constructor called" << std::endl;
}

Cat::Cat(const Cat& copy): Animal(copy)
{
	std::cout << "Cat: Copy Constructor called" << std::endl;
}

Cat::~Cat()
{
	std::cout << "Cat: Destructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &src)
{
	std::cout << "Cat: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
		Animal::operator=(src);
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << this->_type << ": Meovv!!" << std::endl;
}
