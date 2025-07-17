#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Default"), hitPoints(initHitPoints), energyPoints(initEnergyPoints), attackDamage(initAttackDamage)
{
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string _name) : name(_name), hitPoints(initHitPoints), energyPoints(initEnergyPoints), attackDamage(initAttackDamage)
{
	std::cout << "Constructor for "<< _name <<" called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copy)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor for "<< this->name <<" called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &src)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->name = src.name;
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
		std::cout << this->name << " cannot attack " << target;
		std::cout << ", because " << this->name << " has no HP." << std::endl;
		return ;
	}
	if (this->energyPoints == 0)
	{
		std::cout << this->name << " cannot attack " << target;
		std::cout << ", because " << this->name << " has no EP left." << std::endl;
		return ;
	}
	std::cout << this->name << " attacks " << target; 
	std::cout << ", causing " << this->attackDamage << " points of damage!" << std::endl;
	this->energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->hitPoints == 0)
	{
		std::cout << this->name << " is already dead, stop beating it." << std::endl;
		return ;
	}
	if (this->hitPoints > amount)
		this->hitPoints = this->hitPoints - amount;
	else
		this->hitPoints = 0;
	std::cout
			<< this->name << " take " << amount << " damage. " 
			<< "He has " << this->hitPoints << " HP." << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
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

const std::string ClapTrap::getName(void) const
{
	return (this->name);
}
