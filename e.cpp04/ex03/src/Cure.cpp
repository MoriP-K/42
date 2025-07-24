#include "../inc/Cure.hpp"
#include "../inc/ICharacter.hpp"

Cure::Cure(): AMateria("cure")
{
	std::cout << "Cure: Constructor called" << std::endl;
}

Cure::Cure(const Cure& copy): AMateria(copy)
{
	std::cout << "Cure: Copy Constructor Called" << std::endl;
}

Cure::~Cure()
{
	std::cout << "Cure: Destructor called" << std::endl;
}

Cure &Cure::operator=(const Cure &src)
{
	std::cout << "Cure: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		AMateria::operator=(src);
	}
	return (*this);
}

AMateria* Cure::clone(void) const
{
	std::cout << "Cure clone() called" << std::endl;
	return (new Cure(*this));
}

void Cure::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}