#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string _name) : ClapTrap(_name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap Constructor for " << _name << " called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
	std::cout << "FragTrap Copy constructor called" << std::endl;
	*this = copy;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor for " << this->name << " called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
	std::cout << "FragTrap Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->name = src.name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return (*this);
}

void FragTrap::beRepaired(unsigned int amount)
{
	if (this->hitPoints == 0)
	{
		std::cout << this->name << " cannot repair itself, because " << this->name << " is dead." << std::endl;
		return ;
	}
	if (this->energyPoints == 0)
	{
		std::cout << this->name << " cannot repair itself, because " << this->name << " has no EP." << std::endl;
		return ;
	}
	unsigned int actualRepair = amount;
	if (this->hitPoints + amount > initHitPoints)
	{
		actualRepair = initHitPoints - this->hitPoints;
		this->hitPoints = initHitPoints;
	}
	else
		this->hitPoints = this->hitPoints + amount;
	this->energyPoints--;
	std::cout
		<< this->name << " repaired " << actualRepair << " HP, he has " << this->hitPoints << " HP now. "
		<< this->name << " has " << this->energyPoints << " EP left." << std::endl;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->name << ": You want me a high five?\n\t*WHAMM*\nHere you go." << std::endl;
}
