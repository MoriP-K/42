#include "../inc/ClapTrap.hpp"
#include "../inc/ScavTrap.hpp"

int	main(void)
{
	ClapTrap	trapA("Mori");
	std::cout << std::endl;
	ScavTrap	trapB("Yama");
	std::cout << std::endl;

	trapB.guardGate();
	std::cout << std::endl;

	trapA.attack(trapB.getName());
	trapB.takeDamage(0);
	std::cout << std::endl;

	trapA.beRepaired(5);
	std::cout << std::endl;

	for (int i = 0; i < 9; i++)
		trapA.attack(trapB.getName());
	std::cout << std::endl;

	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;

	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;

	trapA.beRepaired(5);
	std::cout << std::endl;

	trapA.attack(trapB.getName());
	std::cout << std::endl;

	trapB.beRepaired(4);
	std::cout << std::endl;

	return (0);
}
