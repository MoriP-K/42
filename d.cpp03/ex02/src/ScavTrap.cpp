#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	this->hitPoints = initHitPoints;
	this->energyPoints = initEnergyPoints;
	this->attackDamage = initAttackDamage;
	this->guardingGate = false;
	std::cout << "ScavTrap Default constructor called" << std::endl;
}
ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	this->hitPoints = initHitPoints;
	this->energyPoints = initEnergyPoints;
	this->attackDamage = initAttackDamage;
	this->guardingGate = false;
	std::cout << "ScavTrap Constructor for " << this->name << " called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy): ClapTrap(copy)
{
	this->guardingGate = copy.guardingGate;
	std::cout << "ScavTrap Copy constructor called" << std::endl;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor for " << this->name << " called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src)
{
	std::cout << "ScavTrap Assignment operator called" << std::endl;
	if (this != &src)
	{
		ClapTrap::operator=(src);
		this->guardingGate = src.guardingGate;
	}
	return (*this);
}

void ScavTrap::attack(const std::string &target)
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

void ScavTrap::beRepaired(unsigned int amount)
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

void ScavTrap::guardGate(void)
{
	if (this->guardingGate == false)
	{
		this->guardingGate = true;
		std::cout << "ScavTrap " << this->name << " is now guarding the gate." << std::endl;
	}
	else
		std::cout << "ScavTrap " << this->name << " is already guarding gate." << std::endl;
}
