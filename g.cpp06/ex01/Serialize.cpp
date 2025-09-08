#include "Serialize.hpp"

Serialize::Serialize()
{
}

Serialize::Serialize(const Serialize& copy)
{
	*this = copy;
}

Serialize &Serialize::operator=(const Serialize &src)
{
	if (this != &src)
	{
		*this = src;
	}
	return (*this);
}

Serialize::~Serialize()
{
}

uintptr_t Serialize::serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* Serialize::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data*>(raw));
}
