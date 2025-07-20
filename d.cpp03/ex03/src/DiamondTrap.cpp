#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(): ClapTrap("default-DT_clap_name"), ScavTrap(), FragTrap()
{
	this->_name = "default-DT";
	this->hitPoints = FragTrap::hitPoints;
	this->energyPoints = ScavTrap::energyPoints;
	this->attackDamage = FragTrap::attackDamage;
	std::cout << "DiamondTrap Default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& copy): ClapTrap(copy), ScavTrap(copy), FragTrap(copy)
{
	*this = copy;
	std::cout << "DiamondTrap Copy constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name): ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap()
{
	this->_name = name;
	this->hitPoints = FragTrap::hitPoints;
	this->energyPoints = ScavTrap::energyPoints;
	this->attackDamage = FragTrap::attackDamage;
	std::cout << "DiamondTrap Constructor for "<< this->_name <<" called" << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap Destrcutor for " << this->_name << " called" << std::endl;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &src)
{
	std::cout << "DiamondTrap Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		ClapTrap::operator=(src);
	}
	return (*this);
}

void DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI(void)
{
	std::cout << "I'm DiamondTrap: " << this->_name
		<< ", I'm originated from ClapTrap: " << ClapTrap::_name << std::endl;
}
