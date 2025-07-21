#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap: virtual public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(const FragTrap &copy);
	~FragTrap();

	FragTrap &operator=(const FragTrap &src);

	void highFivesGuys(void);

protected:
	static const unsigned int INIT_HP = 100;
	static const unsigned int INIT_EP = 100;
	static const unsigned int INIT_AT = 30;
};

#endif
