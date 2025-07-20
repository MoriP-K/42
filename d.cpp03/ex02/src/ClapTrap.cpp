#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Default"), hitPoints(100), energyPoints(100), attackDamage(30)
{
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), hitPoints(100), energyPoints(100), attackDamage(30)
{
	std::cout << "Constructor for "<< name <<" called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor for "<< this->_name <<" called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return (*this);
}

void ClapTrap::attack(const std::string& target)
{
	if (this->hitPoints == 0)
	{
		std::cout << this->_name << " cannot attack " << target;
		std::cout << ", because " << this->_name << " has no HP." << std::endl;
		return ;
	}
	if (this->energyPoints == 0)
	{
		std::cout << this->_name << " cannot attack " << target;
		std::cout << ", because " << this->_name << " has no EP left." << std::endl;
		return ;
	}
	std::cout << this->_name << " attacks " << target; 
	std::cout << ", causing " << this->attackDamage << " points of damage!" << std::endl;
	this->energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->hitPoints == 0)
	{
		std::cout << this->_name << " is already dead, stop beating it." << std::endl;
		return ;
	}
	if (this->hitPoints > amount)
		this->hitPoints = this->hitPoints - amount;
	else
		this->hitPoints = 0;
	std::cout
			<< this->_name << " take " << amount << " damage. " 
			<< "He has " << this->hitPoints << " HP." << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->hitPoints == 0)
	{
		std::cout << this->_name << " cannot repair itself, because " << this->_name << " is dead." << std::endl;
		return ;
	}
	if (this->energyPoints == 0)
	{
		std::cout << this->_name << " cannot repair itself, because " << this->_name << " has no EP." << std::endl;
		return ;
	}
	unsigned int actualRepair = amount;
	if (this->hitPoints + amount > 100)
	{
		actualRepair = 100 - this->hitPoints;
		this->hitPoints = 100;
	}
	else
		this->hitPoints = this->hitPoints + amount;
	this->energyPoints--;
	std::cout
		<< this->_name << " repaired " << actualRepair << " HP, he has " << this->hitPoints << " HP now. "
		<< this->_name << " has " << this->energyPoints << " EP left." << std::endl;
}

const std::string ClapTrap::getName(void) const
{
	return (this->_name);
}
