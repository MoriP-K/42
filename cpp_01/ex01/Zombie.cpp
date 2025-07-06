#include "Zombie.hpp"

Zombie::Zombie()
{
}

Zombie::Zombie(std::string zombieName)
{
	name = zombieName;
}

Zombie::~Zombie()
{
}

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
