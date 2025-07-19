#include "Animal.hpp"

Animal::Animal()
{
}

Animal::Animal(const Animal& copy)
{
	*this = copy;
}

Animal::~Animal()
{
}

Animal &Animal::operator=(const Animal &src)
{
	if (this != &src)
		*this = src;
	return (*this);
}

std::string Animal::getType(void)
{
	return (this->type);
}

void Animal::makeSound(void)
{
	std::cout << "Barking << " << this->type << std::endl;
}