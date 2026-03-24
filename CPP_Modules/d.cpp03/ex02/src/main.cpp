#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap trapC("CT");
	std::cout << std::endl;
	ScavTrap trapS("ST");
	std::cout << std::endl;
	FragTrap trapF("FT");
	std::cout << std::endl;

	trapF.highFivesGuys();
	std::cout << std::endl;

	trapC.beRepaired(3);
	std::cout << std::endl;

	for (int i = 0; i < 10; i++)
		trapC.attack("test");
	std::cout << std::endl;

	trapS.guardGate();
	std::cout << std::endl;

	trapF.attack(trapC.getName());
	trapC.takeDamage(30);
	std::cout << std::endl;

	trapF.attack(trapC.getName());
	trapC.takeDamage(30);
	std::cout << std::endl;

	trapC.beRepaired(3);
	std::cout << std::endl;

	trapS.attack(trapF.getName());
	trapF.takeDamage(20);
	std::cout << std::endl;

	trapF.beRepaired(10);
	std::cout << std::endl;


	trapF.attack(trapS.getName());
	trapS.takeDamage(30);
	std::cout << std::endl;

	trapF.attack(trapS.getName());
	trapS.takeDamage(30);
	std::cout << std::endl;

	trapF.attack(trapS.getName());
	trapS.takeDamage(30);
	std::cout << std::endl;

	trapF.attack(trapS.getName());
	trapS.takeDamage(30);
	std::cout << std::endl;

	trapF.attack(trapS.getName());
	trapS.takeDamage(30);
	std::cout << std::endl;

	return (0);
}
