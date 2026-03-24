#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <iostream>
#include "Data.hpp"
#include <stdint.h>

class Serializer
{
private:
	Serializer();
	Serializer(const Serializer& copy);
	Serializer& operator=(const Serializer &src);
	~Serializer();

public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

#endif
