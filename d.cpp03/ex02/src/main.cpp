#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap trapA("Hugo"); // HP=10, EP=10, AD=0
	ScavTrap trapB("Tom"); // HP=100, EP=50, AD=20
	FragTrap trapC("Paul"); // HP=100, EP=100, AD=30 

	trapC.highFivesGuys();

	trapA.attack(trapB.getName());
	trapB.takeDamage(0);

	trapB.guardGate();

	trapC.attack(trapA.getName());
	trapA.takeDamage(30);

	trapA.attack(trapB.getName());
	trapB.takeDamage(0);

	trapB.attack(trapC.getName());
	trapC.takeDamage(20);

	trapC.attack(trapA.getName());
	trapA.takeDamage(30);
	trapA.beRepaired(3);

	trapB.attack(trapA.getName());
	trapA.takeDamage(20);

	trapC.attack(trapB.getName());
	trapB.takeDamage(30);

	trapA.attack(trapB.getName());
	trapB.takeDamage(0);

	trapB.attack(trapC.getName());
	trapC.takeDamage(20);

	trapC.attack(trapA.getName());
	trapA.takeDamage(30);
	trapA.beRepaired(3);

	trapB.attack(trapA.getName());
	trapA.takeDamage(20);

	trapC.attack(trapB.getName());
	trapB.takeDamage(30);

	trapC.beRepaired(5);

	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);
	trapA.beRepaired(3);

	return (0);
}
