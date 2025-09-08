#include "Serialize.hpp"
#include "Data.hpp"

int main(void)
{
	Data *data = new Data;

	data->id = 42;
	data->name = "kmoriyam";

	uintptr_t raw = Serialize::serialize(data);
	Data *serialized = Serialize::deserialize(raw);

	std::cout << serialized->id << std::endl;
	std::cout << serialized->name << std::endl;

	delete data;
}