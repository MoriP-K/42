#include "Weapon.hpp"

Weapon::Weapon()
{
}

Weapon::Weapon(std::string type)
{
	this->type = type;
}

Weapon::~Weapon()
{
}

void Weapon::setType(std::string newType)
{
	this->type = newType;
}

const std::string& Weapon::getType(void) const
{
	return (this->type);
}
