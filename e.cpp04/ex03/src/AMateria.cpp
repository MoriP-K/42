#include "../inc/AMateria.hpp"

AMateria::AMateria(std::string const &type): _type(type)
{
	// std::cout << "AMateria: Constructor for " << this->_type << " called" << std::endl;
}

AMateria::AMateria(const AMateria& copy): _type(copy._type)
{
	// std::cout << "AMateria: Copy Constructor Called" << std::endl;
}

AMateria::~AMateria()
{
	// std::cout << "AMateria: Destructor for " << this->_type << " called" << std::endl;
}

AMateria &AMateria::operator=(const AMateria &src)
{
	// std::cout << "AMateria: Copy assignment operator called" << std::endl;
	(void)src;
	return (*this);
}

std::string const & AMateria::getType(void) const
{
	return (this->_type);
}

void AMateria::use(ICharacter& target)
{
	// std::cout << "AMateria " << this->_type << " used on " << target.getName() << std::endl;
	(void)target;
}
