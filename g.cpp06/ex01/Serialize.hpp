#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

class Serialize
{
private:
	Serialize();
	Serialize(const Serialize& copy);
	Serialize& operator=(const Serialize &src);
	~Serialize();

public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

#endif
