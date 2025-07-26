#include "../inc/Character.hpp"

AMateria* Character::floor[100];
int Character::floorCount = 0;

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
	for (int i = 0; i < slot; i++)
	{
		if (this->inventory[i] == NULL)
		{
			this->inventory[i] = m;
			std::cout << this->_name << " equipped " << m->getType() << " in slot " << i << std::endl;
			return ;
		}
	}
	std::cout << this->_name << "'s inventory is full, cannot equip " << m->getType() << std::endl;
	this->dropToFloor(m);
}

void Character::unequip(int idx)
{
	if (idx < 0 || idx >= slot)
	{
		std::cout << "Invalid slot index: " << idx << std::endl;
		return ;
	}
	if (this->inventory[idx] == NULL)
	{
		std::cout << "No materia in slot " << idx << " to unequip" << std::endl;
		return ;
	}
	std::cout<< this->_name << " unequipped " << this->inventory[idx]->getType() << " from slot " << idx << std::endl;
	this->dropToFloor(this->inventory[idx]);
	this->inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
	if (idx < 0 || idx >= slot)
	{
		std::cout << "Invalid slot index: " << idx << std::endl;
		return ;
	}
	if (this->inventory[idx] == NULL)
	{
		std::cout << "No materia in slot " << idx << "to use" << std::endl;
		return ;
	}
	std::cout << this->_name << " uses " << this->inventory[idx]->getType() << " on " << target.getName() << ": " << std::endl;
	this->inventory[idx]->use(target);
}

void Character::showFloor(void)
{
	std::cout << "==== Floor Items (" << floorCount << "/" << floorSize << ") ====" << std::endl;
	if (floorCount == 0)
	{
		std::cout << "Floor is empty" << std::endl;
	}
	else
	{
		for (int i = 0; i < floorCount; i++)
		{
			std::cout << " " << i << ": " << floor[i]->getType()
				<< " (address: " << floor[i] << ")" << std::endl;
		}
	}
	std::cout << "=============================" << std::endl;
}

void Character::cleanupFloor(void)
{
	if (floorCount > 0)
	{
		std::cout << "\nCleaning up " << floorCount << " items from floor..." << std::endl;
		for (int i = 0; i < floorCount; i++)
		{
			std::cout << "Destroying " << floor[i]->getType() << std::endl;
			delete floor[i];
			floor[i] = NULL;
		}
		floorCount = 0;
		std::cout << "Floor cleaned!" << std::endl;
	}
	else
	{
		std::cout << "Floor is already clean" << std::endl;
	}
}

void Character::clearInventory(void)
{
	std::cout << "Character: clearInventory() called" << std::endl;
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
	std::cout << "Character: copyInventory() called" << std::endl;
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
	std::cout << "Character: initInventory() called" << std::endl;
	for (int i = 0; i < slot; i++)
	{
		this->inventory[i] = NULL;
	}
}

void Character::dropToFloor(AMateria* m)
{
	if (floorCount < floorSize)
	{
		floor[floorCount] = m;
		floorCount++;
		std::cout << m->getType() << " dropped on floor (floor items: "
			<< floorCount << "/" << floorSize << ")" << std::endl;
	}
	else
	{
		std::cout << "Floor is full!! " << m->getType() << " destroyed" << std::endl;
		delete m;
	}
}
