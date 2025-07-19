#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "DiamondTrap.hpp"

int	main(void)
{
	std::cout << "=== DiamondTrap Test ===" << std::endl;
    
    DiamondTrap diamond("TestDiamond");
    
    std::cout << "\n=== Basic Info ===" << std::endl;
    diamond.whoAmI();
    
    std::cout << "\n=== Inherited Methods ===" << std::endl;
    diamond.attack("Enemy");
    diamond.guardGate();        // ScavTrapから継承
    diamond.highFivesGuys();    // FragTrapから継承
    
    std::cout << "\n=== Stats ===" << std::endl;
    std::cout << "HP: 100 (FragTrap), EP: 50 (ScavTrap), AD: 30 (FragTrap)" << std::endl;
    
	// ClapTrap	trapA("AAA");
	// std::cout << std::endl;
	// ScavTrap	trapB("BBB");
	// std::cout << std::endl;
	// FragTrap	trapC("CCC");
	// std::cout << std::endl;
	// DiamondTrap	trapD("DDD");
	// std::cout << std::endl;

	// trapD.attack("everyone!");
	// trapD.whoAmI();
	// trapD.highFivesGuys();
	// trapD.guardGate();
	// std::cout << std::endl;

	// trapC.highFivesGuys();
	// trapC.attack(trapD.getName());
	// std::cout << std::endl;
	
	// trapD.guardGate();
	// std::cout << std::endl;

	// trapD.attack(trapC.getName());
	// trapB.takeDamage(20);
	// std::cout << std::endl;

	// trapA.attack(trapB.getName());
	// trapB.takeDamage(2);
	// std::cout << std::endl;

	// trapB.attack(trapC.getName());
	// trapC.takeDamage(7);
	// std::cout << std::endl;

	// trapC.attack(trapA.getName());
	// trapA.takeDamage(5);
	// std::cout << std::endl;

	// trapA.beRepaired(3);
	// std::cout << std::endl;

	// trapB.attack(trapA.getName());
	// trapA.takeDamage(2);
	// std::cout << std::endl;

	// trapC.attack(trapB.getName());
	// trapB.takeDamage(2);

	// trapA.attack(trapB.getName());
	// trapB.takeDamage(2);
	// std::cout << std::endl;

	// trapB.attack(trapC.getName());
	// trapC.takeDamage(7);
	// std::cout << std::endl;

	// trapC.attack(trapA.getName());
	// trapA.takeDamage(5);
	// std::cout << std::endl;

	// trapA.beRepaired(3);
	// std::cout << std::endl;

	// trapB.attack(trapA.getName());
	// trapA.takeDamage(2);
	// std::cout << std::endl;

	// trapC.attack(trapB.getName());
	// std::cout << std::endl;

	// trapC.beRepaired(5);
	// trapA.beRepaired(3);
	// trapB.beRepaired(3);
	// trapD.beRepaired(6);
	// std::cout << std::endl;

	return (0);
}
