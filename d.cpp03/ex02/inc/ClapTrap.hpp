#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
protected:
	std::string	name;
	unsigned int 	hitPoints;
	unsigned int	energyPoints;
	unsigned int	attackDamage;

public:
	ClapTrap();
	ClapTrap(std::string _name);
	ClapTrap(const ClapTrap& copy);
	virtual ~ClapTrap();

	ClapTrap &operator=(const ClapTrap &src);

	virtual void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	virtual void beRepaired(unsigned int amount);

	const std::string getName(void) const;
};

#endif
