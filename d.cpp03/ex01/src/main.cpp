#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap	trapA("Mori");
	std::cout << std::endl;
	ScavTrap	trapB("Yama");
	std::cout << std::endl;

	trapB.guardGate();
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(20);
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(20);
	std::cout << std::endl;

	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.beRepaired(5);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.beRepaired(5);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(20);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.beRepaired(3);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(20);
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	std::cout << std::endl;
	trapB.beRepaired(5);
	trapA.beRepaired(3);
	std::cout << std::endl;

	return (0);
}
