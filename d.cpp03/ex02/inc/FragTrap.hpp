#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &copy);
	virtual ~FragTrap();

	FragTrap &operator=(const FragTrap &src);

	void beRepaired(unsigned int amount);
	void highFivesGuys(void);

protected:
	static unsigned int const initHitPoints = 100;
	static unsigned int const initEnergyPoints = 100;
	static unsigned int const initAttackDamage = 30;
};

#endif
