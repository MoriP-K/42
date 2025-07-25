#include "../inc/Character.hpp"

Character::Character(): _name("default")
{
	// std::cout << "Character: Default Constructor called" << std::endl;
	this->initInventory();
}

Character::Character(std::string const &name): _name(name)
{
	// std::cout << "Character: Constructor for " << this->_name << " called" << std::endl;
	this->initInventory();
}

Character::Character(const Character &copy): _name(copy._name)
{
	// std::cout << "Character: Copy Constructor called" << std::endl;
	this->initInventory();
	this->copyInventory(copy);
}

Character::~Character()
{
	// std::cout << "Character: Destructor for " << this->_name <<" called" << std::endl;
	this->clearInventory();
}

Character &Character::operator=(const Character &src)
{
	// std::cout << "Character: Copy assignment operator called" << std::endl;
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
		// std::cout << "Cannot equip null materia" << std::endl;
		return ;
	}
	for (int i = 0; i < slot; i++)
	{
		if (this->inventory[i] == NULL)
		{
			this->inventory[i] = m;
			// std::cout << this->_name << " equipped " << m->getType() << " in slot " << i << std::endl;
			return ;
		}
	}
	// std::cout << this->_name << "'s inventory is full, cannot equip " << m->getType() << std::endl;
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= slot)
	{
		// std::cout << "Invalid slot index: " << idx << std::endl;
		return ;
	}
	if (this->inventory[idx] == NULL)
	{
		// std::cout << "No materia in slot " << idx << " to unequip" << std::endl;
		return ;
	}
	// std::cout<< this->_name << "unequippe " << this->inventory[idx]->getType() << " from slot " << idx << std::endl;
	this->inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= slot)
	{
		// std::cout << "Invalid slot index: " << idx << std::endl;
		return ;
	}
	if (this->inventory[idx] == NULL)
	{
		// std::cout << "No materia in slot " << idx << "to use" << std::endl;
		return ;
	}
	// std::cout << this->_name << " uses " << this->inventory[idx]->getType() << " on " << target.getName() << ": " << std::endl;
	this->inventory[idx]->use(target);
}

void Character::clearInventory(void)
{
	for (int i = 0; i < slot; i++)
	{
		if (this->inventory[i])
		{
			delete this->inventory[i];
			this->inventory[i] = NULL;
		}
	}
}

void Character::copyInventory(const Character &src)
{
	for (int i = 0; i < slot; i++)
	{
		if (src.inventory[i])
		{
			this->inventory[i] = src.inventory[i]->clone();
		}
		else
		{
			this->inventory[i] = NULL;
		}
	}
}

void Character::initInventory(void)
{
	for (int i = 0; i < slot; i++)
	{
		this->inventory[i] = NULL;
	}
}
