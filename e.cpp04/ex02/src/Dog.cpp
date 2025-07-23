#include "../inc/Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << "Dog: Default Constructor called" << std::endl;
	this->brain = new Brain();
}

Dog::Dog(const Dog& copy)
{
	std::cout << "Dog: Copy Constructor called" << std::endl;
	*this = copy;
}

Dog::~Dog()
{
	std::cout << "Dog: Destructor called" << std::endl;
	delete this->brain;
}

Dog &Dog::operator=(const Dog &src)
{
	std::cout << "Dog: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		Animal::operator=(src);
		this->brain = new Brain();
		*this->brain = *src.brain;
	}
	return (*this);
}

void Dog::makeSound(void) const
{
	std::cout << this->_type << ": Bow wow!!" << std::endl;
}

Brain* Dog::getBrain(void) const
{
	std::cout << "Dog::getBrain() called, brain address: " << this->brain << std::endl;
	return (this->brain);
}
