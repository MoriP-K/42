#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap: virtual public ClapTrap
{
private:
	bool guardingGate;

public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap &copy);
	~ScavTrap();

	ScavTrap &operator=(const ScavTrap &src);

	void attack(const std::string &target);
	void guardGate(void);

protected:
	static const unsigned int INIT_HP = 100;
	static const unsigned int INIT_EP = 50;
	static const unsigned int INIT_AT = 20;
};

#endif
