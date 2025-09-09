#include "Serializer.hpp"
#include "Data.hpp"

int	main(void)
{
	Data *data = new Data;
	data->id = 42;
	data->name = "kmoriyam";

	uintptr_t raw = Serializer::serialize(data);
	Data *serialized = Serializer::deserialize(raw);

	std::cout << "Original:     " << data << std::endl;
	std::cout << "Deserialized: " << serialized << std::endl;
	std::cout << "Are equal:    " << (data == serialized ? "YES" : "NO") << std::endl;

	std::cout << "ID:   " << serialized->id << std::endl;
	std::cout << "NAME: " << serialized->name << std::endl;
	delete		data;
}
