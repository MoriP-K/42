#include "../inc/Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain: Default Constructor called" << std::endl;
}

Brain::Brain(const Brain& copy)
{
	std::cout << "Brain: Copy Constructor called" << std::endl;
	*this = copy;
}

Brain::~Brain()
{
	std::cout << "Brain: Destructor called" << std::endl;
}

Brain &Brain::operator=(const Brain &src)
{
	std::cout << "Brain: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		for (int i = 0; i < brainMemory; i++)
		{
			this->ideas[i] = src.ideas[i];
		}
	}
	return (*this);
}
