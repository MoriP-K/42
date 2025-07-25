#include "../inc/Character.hpp"

Character::Character(): _name("default")
{
	std::cout << "Character: Default Constructor called" << std::endl;
	this->initInventory();
}

Character::Character(std::string const &name): _name(name)
{
	std::cout << "Character: Constructor for " << this->_name << " called" << std::endl;
	this->initInventory();
}

Character::Character(const Character &copy): _name(copy._name)
{
	std::cout << "Character: Copy Constructor called" << std::endl;
	this->initInventory();
	this->copyInventory(copy);
}

Character::~Character()
{
	std::cout << "Character: Destructor for " << this->_name <<" called" << std::endl;
	this->clearInventory();
}

Character &Character::operator=(const Character &src)
{
	std::cout << "Character: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		this->clearInventory();
		this->copyInventory(src);
	}
	return (*this);
}

std::string const & Character::getName(void) const
{
	return (this->_name);
}

void Character::equip(AMateria *m)
{
	if (!m)
	{
		std::cout << "Cannot equip null materia" << std::endl;
		return ;
	}
}

void Character::initInventory(void)
{
	for (int i = 0; i < slot; i++)
	{
		this->inventory[i] = nullptr;
	}
}
