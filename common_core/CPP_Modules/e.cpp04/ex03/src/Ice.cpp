#include "../inc/Ice.hpp"
#include "../inc/ICharacter.hpp"

Ice::Ice(): AMateria("ice")
{
	std::cout << "Ice: Constructor called" << std::endl;
}

Ice::Ice(const Ice& copy): AMateria(copy)
{
	std::cout << "Ice: Copy Constructor Called" << std::endl;
}

Ice::~Ice()
{
	std::cout << "Ice: Destructor called" << std::endl;
}

Ice &Ice::operator=(const Ice &src)
{
	std::cout << "Ice: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		AMateria::operator=(src);
	}
	return (*this);
}

AMateria* Ice::clone(void) const
{
	std::cout << "Ice clone() called" << std::endl;
	return (new Ice(*this));
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
