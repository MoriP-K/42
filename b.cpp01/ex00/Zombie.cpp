#include "Zombie.hpp"

Zombie::Zombie()
{
}

Zombie::Zombie(std::string zombieName): name(zombieName)
{
}

Zombie::~Zombie()
{
	std::cout << name << " is destroyed." << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
