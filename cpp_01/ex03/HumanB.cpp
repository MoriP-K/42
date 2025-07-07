#include "HumanB.hpp"

HumanB::HumanB(std::string name, std::string type): name(name), type(type)
{
}

HumanB::HumanB()
{
}

HumanB::~HumanB()
{
}

void HumanB::attack(void)
{
	std::cout << name << "  attacks with their " << type << std::endl;
}
