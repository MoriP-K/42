#include "Bereaucrat.hpp"

Bereaucrat::Bereaucrat()
{
	std::cout << "Bereaucrat: Default Constructor called" << std::endl;
}

Bereaucrat::Bereaucrat(std::string name): _name(name)
{
	std::cout << "Bereaucrat: Constructor for " << name <<" called" << std::endl;
}

Bereaucrat::Bereaucrat(const Bereaucrat& copy): _name(copy._name)
{
	std::cout << "Bereaucrat: Copy Constructor called" << std::endl;
}

Bereaucrat::~Bereaucrat()
{
	std::cout << "Bereaucrat: Destructor called" << std::endl;
}

Bereaucrat &Bereaucrat::operator=(const Bereaucrat &src)
{
	
}