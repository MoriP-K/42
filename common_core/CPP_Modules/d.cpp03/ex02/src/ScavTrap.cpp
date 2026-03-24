#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->guardingGate = false;
	std::cout << "ScavTrap Default constructor called" << std::endl;
}
ScavTrap::ScavTrap(std::string _name): ClapTrap(_name)
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->guardingGate = false;
	std::cout << "ScavTrap Constructor for " << this->_name << " called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy): ClapTrap(copy)
{
	std::cout << "ScavTrap Copy constructor called" << std::endl;
	*this = copy;
	this->guardingGate = copy.guardingGate;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor for " << this->_name << " called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &src)
{
	std::cout << "ScavTrap Assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		this->guardingGate = src.guardingGate;
		ClapTrap::operator=(src);
	}
	return (*this);
}

void ScavTrap::attack(const std::string &target)
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

void ScavTrap::guardGate(void)
{
	if (this->guardingGate == false)
	{
		this->guardingGate = true;
		std::cout << "ScavTrap " << this->_name << " is now guarding the gate." << std::endl;
	}
	else
		std::cout << "ScavTrap " << this->_name << " is already guarding gate." << std::endl;
}
