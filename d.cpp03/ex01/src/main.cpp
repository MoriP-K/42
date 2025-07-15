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
	for (int i = 0; i < 12; i++)
		B.attack("YamaP-CLONE");
	B.beRepaired(3);
	return (0);
}
