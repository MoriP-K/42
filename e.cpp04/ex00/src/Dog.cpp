#include "../inc/Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Dog: Default Constructor called" << std::endl;
}

Dog::Dog(const Dog& copy): Animal(copy)
{
	std::cout << "Dog: Copy Constructor called" << std::endl;
}

Dog::~Dog()
{
	std::cout << "Dog: Destructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &src)
{
	std::cout << "Dog: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
		Animal::operator=(src);
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << this->_type << ": Bow wow!!" << std::endl;
}
