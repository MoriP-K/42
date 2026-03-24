#include "../inc/WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): _type("WrongAnimal")
{
	std::cout << "WrongAnimal: Default Constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): _type(type)
{
	std::cout << "WrongAnimal: Constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& copy): _type(copy._type)
{
	std::cout << "WrongAnimal: Copy Constructor Called" << std::endl;
}

WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal: Destructor called" << std::endl;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &src)
{
	std::cout << "WrongAnimal: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
	}
	return (*this);
}

void WrongAnimal::makeSound(void) const
{
	std::cout << this->getType() << ": What?!? No audio!!" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
	return (this->_type);
}
