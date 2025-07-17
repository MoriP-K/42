#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap: public ClapTrap
{
private:
	bool guardingGate;

public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap &copy);
	virtual ~ScavTrap();

	ScavTrap &operator=(const ScavTrap &src);

	void attack(const std::string &target);
	void beRepaired(unsigned int amount);
	void guardGate(void);

protected:
	static unsigned int const initHitPoints = 100;
	static unsigned int const initEnergyPoints = 50;
	static unsigned int const initAttackDamage = 20;
};

#endif
