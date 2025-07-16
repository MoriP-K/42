#include "ScavTrap.hpp"

int main(void)
{
	ClapTrap A;
	ScavTrap B("MoriP");

	A.attack(B.getName());
	B.takeDamage(10);
	B.takeDamage(10);
	B.beRepaired(5);
	A.attack(B.getName());
	B.beRepaired(3);
	for (int i = 0; i < 12; i++)
		A.attack(B.getName());
	B.beRepaired(3);
	return (0);
}
