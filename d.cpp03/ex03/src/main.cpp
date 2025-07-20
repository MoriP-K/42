#include "DiamondTrap.hpp"

int	main(void)
{
	std::cout << "=== DiamondTrap Test ===" << std::endl;
    DiamondTrap A;
    DiamondTrap copyB(A);
    DiamondTrap assignC = A;

    std::cout << "\n=== Who Am I? ===" << std::endl;
    A.whoAmI();
    copyB.whoAmI();
    assignC.whoAmI();

    std::cout << "\n=== Combat System Test ===" << std::endl;
    A.attack(copyB.getName());
	copyB.takeDamage(30);
	A.attack(copyB.getName());
	copyB.takeDamage(30);
	A.attack(copyB.getName());
	copyB.takeDamage(30);
	A.attack(copyB.getName());
	copyB.takeDamage(30);

    std::cout << "\n=== Special Abilities Test ===" << std::endl;
    A.guardGate();        // ScavTrapから継承
    A.highFivesGuys();    // FragTrapから継承

	std::cout << "\n=== Energy System Test ===" << std::endl;
	for (int i = 0; i < 50; i++)
		A.attack("SandBag");

	std::cout << "\n=== Error Hnadling Test ===" << std::endl;
	A.attack("SandBag");
	A.beRepaired(10);
	A.whoAmI();

    std::cout << "\n=== Destructor Chain ===" << std::endl;
	return (0);
}
