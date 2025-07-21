#include "../inc/Animal.hpp"

Animal::Animal(): _type("Animal")
{
	std::cout << "Animal: Default Constructor called" << std::endl;
}

Animal::Animal(std::string type): _type(type)
{
	std::cout << "Animal: Constructor for " << this->_type << " called" << std::endl;
}

Animal::Animal(const Animal& copy)
{
	std::cout << "Animal: Copy Constructor Called" << std::endl;
	*this = copy;
}

Animal::~Animal()
{
	std::cout << "Animal: Destructor for " << this->_type << " called" << std::endl;
}

Animal &Animal::operator=(const Animal &src)
{
	std::cout << "Animal: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
	}
	return (*this);
}

void Animal::makeSound(void) const
{
	std::cout << this->getType() << ": What?!? No audio!!" << std::endl;
}

std::string Animal::getType(void) const
{
	return (this->_type);
}
