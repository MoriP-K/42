#include "HumanA.hpp"

HumanA::HumanA(std::string name, std::string type): name(name), type(type)
{
}

HumanA::~HumanA()
{
}

void HumanA::attack(void)
{
	std::cout << name << "  attacks with their " << getType() << std::endl;
}
