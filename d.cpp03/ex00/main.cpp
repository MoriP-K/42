#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap A;
	ClapTrap B("MoriP");

	A.attack("YamaP");
	A.takeDamage(10);
	A.takeDamage(10);
	A.beRepaired(5);
	A.attack("Other YamaP");
	B.beRepaired(3);
	return 0;
}
