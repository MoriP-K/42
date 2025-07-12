#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string _name, int _hitPoints, int _energyPoints,
	int _attackDamage) : name(_name), hitPoints(_hitPoints),
	energyPoints(_energyPoints), attackDamage(_attackDamage)
{
	std::cout << "Default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copy)
{
	*this = copy;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{

}

void ClapTrap::takeDamage(unsigned int amount)
{

}

void ClapTrap::beRepaired(unsigned int amount)
{
	
}