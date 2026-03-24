#include "../inc/AAnimal.hpp"

AAnimal::AAnimal(): _type("AAnimal")
{
	std::cout << "AAnimal: Default Constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type): _type(type)
{
	std::cout << "AAnimal: Constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal& copy): _type(copy._type)
{
	std::cout << "AAnimal: Copy Constructor Called" << std::endl;
}

AAnimal::~AAnimal()
{
	std::cout << "AAnimal: Destructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &src)
{
	std::cout << "AAnimal: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
	}
	return (*this);
}

void AAnimal::makeSound(void) const
{
	std::cout << this->getType() << ": What?!? No audio!!" << std::endl;
}

std::string AAnimal::getType(void) const
{
	return (this->_type);
}
