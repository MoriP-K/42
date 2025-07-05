#include "Zombie.hpp"

Zombie::Zombie(): name("unknown") {}

Zombie::Zombie(const std::string& zombieName): name(zombieName) {}

Zombie::~Zombie() {
	std::cout << name << " is destroyed." << std::endl;
}

void	Zombie::setName(const std::string& zombieName)
{
	name = zombieName;
}

void	Zombie::announce(void)
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
