#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	if (this->hitPoints == 10)
		this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap Default constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	if (this->hitPoints == 10)
		this->hitPoints = 100;
	this->energyPoints = 100;
	if (this->attackDamage == 0)
		this->attackDamage = 30;
	std::cout << "FragTrap Constructor for " << name << " called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
	std::cout << "FragTrap Copy Constructor called" << std::endl;
	*this = copy;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor for " << this->_name << " called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &src)
{
	std::cout << "FragTrap Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_name = src._name;
		this->hitPoints = src.hitPoints;
		this->energyPoints = src.energyPoints;
		this->attackDamage = src.attackDamage;
	}
	return (*this);
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name << ": You want me a high five?\n\t*WHAMM*\nHere you go." << std::endl;
}
