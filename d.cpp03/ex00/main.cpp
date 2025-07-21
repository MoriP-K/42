#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap A;
	std::cout << std::endl;
	ClapTrap B("MoriP");
	std::cout << std::endl;

	B.beRepaired(5);
	std::cout << std::endl;

	A.attack(B.getName());
	B.takeDamage(10);
	std::cout << std::endl;

	A.attack(B.getName());
	B.takeDamage(10);
	std::cout << std::endl;

	A.attack(B.getName());
	B.takeDamage(10);
	std::cout << std::endl;

	B.beRepaired(5);
	std::cout << std::endl;

	for (int i = 0; i < 9; i++)
		A.attack(B.getName());
	std::cout << std::endl;

	A.beRepaired(5);
	std::cout << std::endl;
	return (0);
}
