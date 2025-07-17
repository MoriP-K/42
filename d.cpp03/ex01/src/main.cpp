#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap	trapA("Mori");
	ScavTrap	trapB("Yama");

	trapB.guardGate();
	trapA.attack(trapB.getName());
	trapB.takeDamage(20);
	trapA.attack(trapB.getName());
	trapB.takeDamage(20);
	trapB.attack(trapA.getName());
	trapA.takeDamage(7);
	trapA.beRepaired(5);
	trapB.attack(trapA.getName());
	trapA.takeDamage(5);
	trapA.beRepaired(5);
	trapB.attack(trapA.getName());
	trapA.takeDamage(2);
	trapA.attack(trapB.getName());
	trapB.takeDamage(2);
	trapB.attack(trapA.getName());
	trapA.takeDamage(7);
	trapA.attack(trapA.getName());
	trapA.takeDamage(5);
	trapA.beRepaired(3);
	trapB.attack(trapA.getName());
	trapA.takeDamage(2);
	trapA.attack(trapB.getName());
	trapB.beRepaired(5);
	trapA.beRepaired(3);

	return (0);
}
