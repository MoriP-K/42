#include "../inc/Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << "Cat: Default Constructor called" << std::endl;
	this->brain = new Brain();
}

Cat::Cat(const Cat &copy): Animal(copy)
{
	std::cout << "Cat: Copy Constructor called" << std::endl;
	this->brain = new Brain(*copy.brain);
}

Cat::~Cat()
{
	std::cout << "Cat: Destructor called" << std::endl;
	delete this->brain;
}

Cat &Cat::operator=(const Cat &src)
{
	std::cout << "Cat: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		Animal::operator=(src);
		*this->brain = *src.brain;
	}
	return (*this);
}

void Cat::makeSound(void) const
{
	std::cout << this->_type << ": Meovv!!" << std::endl;
}

Brain* Cat::getBrain(void) const
{
	return (this->brain);
}
