#include "../inc/WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat: Default Constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& copy): WrongAnimal(copy)
{
	std::cout << "WrongCat: Copy Constructor called" << std::endl;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat: Destructor called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &src)
{
	std::cout << "WrongCat: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_type = src._type;
		WrongAnimal::operator=(src);
	}
	return (*this);
}

void WrongCat::makeSound(void) const
{
	std::cout << this->_type << ": Meovv!!" << std::endl;
}
