#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
protected:
	std::string	_name;
	unsigned int 	hitPoints;
	unsigned int	energyPoints;
	unsigned int	attackDamage;

public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap& copy);
	virtual ~ClapTrap();

	ClapTrap &operator=(const ClapTrap &src);

	virtual void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	const std::string getName(void) const;
};

#endif
