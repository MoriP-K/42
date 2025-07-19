#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap trapA("Alpha");
	std::cout << std::endl;
	ScavTrap trapB("Beta");
	std::cout << std::endl;
	FragTrap trapC("Ganma");
	std::cout << std::endl;

	trapC.highFivesGuys();
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(30);
	std::cout << std::endl;
	trapB.guardGate();
	std::cout << std::endl;
	trapC.attack(trapA.getName());
	trapA.takeDamage(30);
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(30);
	std::cout << std::endl;
	trapB.attack(trapC.getName());
	trapC.takeDamage(30);
	std::cout << std::endl;
	trapC.attack(trapA.getName());
	trapA.takeDamage(30);
	std::cout << std::endl;
	trapA.beRepaired(3);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(30);
	std::cout << std::endl;
	trapC.attack(trapB.getName());
	trapB.takeDamage(30);
	std::cout << std::endl;
	trapA.attack(trapB.getName());
	trapB.takeDamage(30);
	std::cout << std::endl;
	trapC.attack(trapA.getName());
	trapA.takeDamage(30);
	std::cout << std::endl;
	trapA.beRepaired(3);
	std::cout << std::endl;
	trapB.attack(trapA.getName());
	trapA.takeDamage(30);
	std::cout << std::endl;
	trapC.attack(trapB.getName());
	trapB.takeDamage(30);
	std::cout << std::endl;
	trapC.beRepaired(5);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	std::cout << std::endl;

	return (0);
}
