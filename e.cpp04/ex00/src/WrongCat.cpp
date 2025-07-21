#include "../inc/WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << "WrongCat: Default Constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& copy)
{
	std::cout << "WrongCat: Copy Constructor called" << std::endl;
	*this = copy;
}

WrongCat::~WrongCat()
{
	std::cout << "WrongCat: Destructor for " << this->_type <<" called" << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &src)
{
	if (this != &src)
	{
		this->_type = src._type;
		*this = src;
	}
	return (*this);
}

void WrongCat::makeSound(void) const
{
	std::cout << this->_type << ": Meovv!!" << std::endl;
}
