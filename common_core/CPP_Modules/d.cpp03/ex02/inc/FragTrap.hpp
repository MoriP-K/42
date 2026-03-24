#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string _name);
	FragTrap(const FragTrap &copy);
	virtual ~FragTrap();

	FragTrap &operator=(const FragTrap &src);

	void highFivesGuys(void);

};

#endif
