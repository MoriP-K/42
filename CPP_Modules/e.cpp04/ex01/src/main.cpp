#include "../inc/Animal.hpp"
#include "../inc/Dog.hpp"
#include "../inc/Cat.hpp"
#include "../inc/WrongAnimal.hpp"
#include "../inc/WrongCat.hpp"
#include "../inc/Brain.hpp"

int	main(void)
{
	const int num = 4;
	const Animal* animal[num];

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
		std::cout << "type: " << animal[i]->getType();
		std::cout << ", ";
		animal[i]->makeSound();
	}
	std::cout << std::endl;

	std::cout << "=== delete allocated memory ===" << std::endl;
	for (int i = 0; i < num; i++)
	{
		delete animal[i];
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "=== Dog matcha called ===" << std::endl;
	Dog matcha;
	std::cout << std::endl;
	Dog cloneD = matcha;
	std::cout << std::endl;
	Dog anotherD;
	std::cout << std::endl;
	anotherD = matcha;
	std::cout << std::endl;

	std::cout << "=== Dog deep copy ===" << std::endl;
	std::cout << "matcha   address: " << &matcha << std::endl;
	std::cout << "cloneD   address: " << &cloneD << std::endl;
	std::cout << "anotherD address: " << &anotherD << std::endl;
	std::cout << std::endl;

	std::cout << "matcha  : Dog::getBrain() " << matcha.getBrain() << std::endl;
	std::cout << "cloneD  : Dog::getBrain() " << cloneD.getBrain() << std::endl;
	std::cout << "anotherD: Dog::getBrain() " << anotherD.getBrain() << std::endl;
	std::cout << std::endl;

	std::cout << "=== Cat mocha called ===" << std::endl;
	Cat mocha;
	std::cout << std::endl;
	Cat cloneC = mocha;
	std::cout << std::endl;
	Cat anotherC;
	std::cout << std::endl;
	anotherC = mocha;
	std::cout << std::endl;

	std::cout << "=== Cat deep copy ===" << std::endl;
	std::cout << "mocha    address: " << &mocha << std::endl;
	std::cout << "cloneC   address: " << &cloneC << std::endl;
	std::cout << "anotherC address: " << &anotherC << std::endl;
	std::cout << std::endl;

	std::cout << "mocha   : Cat::getBrain() " << mocha.getBrain() << std::endl;
	std::cout << "cloneC  : Cat::getBrain() " << cloneC.getBrain() << std::endl;
	std::cout << "anotherC: Cat::getBrain() " << anotherC.getBrain() << std::endl;
	std::cout << std::endl;

	std::cout << "=== destructor called ===" << std::endl;
	return (0);
}
