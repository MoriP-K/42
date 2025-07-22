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
	if (this != &src)
	{
		for (int i = 0; i < 100; i++)
		{
			if (src.ideas[i].length() > 0)
				this->ideas[i]assign(src.ideas[i]);
		}
	}
	return (*this);
}
