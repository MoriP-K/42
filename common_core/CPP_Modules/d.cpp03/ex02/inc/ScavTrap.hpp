#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
private:
	bool guardingGate;

public:
	ScavTrap();
	ScavTrap(std::string _name);
	ScavTrap(const ScavTrap &copy);
	virtual ~ScavTrap();

	ScavTrap &operator=(const ScavTrap &src);

	void attack(const std::string &target);
	void guardGate(void);
};

#endif
