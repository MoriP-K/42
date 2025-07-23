#include "../inc/Animal.hpp"
#include "../inc/Dog.hpp"
#include "../inc/Cat.hpp"
#include "../inc/WrongAnimal.hpp"
#include "../inc/WrongCat.hpp"
#include "../inc/Brain.hpp"

int	main(void)
{
	const Animal* animal[10];
	const int num = 4;

	std::cout << "\n=== initialization ===" << std::endl;
	for (int i = 0; i < num; i++)
	{
		if (i % 2 == 0)
			animal[i] = new Dog();
		else
			animal[i] = new Cat();
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== type & sound ===" << std::endl;
	for (int i = 0; i < num; i++)
	{
		std::cout << "Animal type: " << animal[i]->getType();
		std::cout << ", ";
		animal[i]->makeSound();
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== delete allocated memory ===" << std::endl;
	for (int i = 0; i < num; i++)
	{
		delete animal[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== matcha called ===" << std::endl;
	Dog matcha;
	std::cout << std::endl;
	Dog clone = matcha;
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "=== destructor called ===" << std::endl;
	return (0);
}
