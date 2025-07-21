#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal* animal = new Animal();
	std::cout << std::endl;
	const Animal* dog = new Dog();
	std::cout << std::endl;
	const Animal* cat = new Cat();
	std::cout << std::endl;
	const WrongAnimal* wrongAnimal = new WrongAnimal();
	std::cout << std::endl;
	const WrongAnimal* wrongCat = new WrongCat();
	std::cout << std::endl;

	std::cout << animal->getType() << " " << std::endl;
	std::cout << dog->getType() << " " << std::endl;
	std::cout << cat->getType() << " " << std::endl;
	std::cout << wrongAnimal->getType() << " " << std::endl;
	std::cout << wrongCat->getType() << " " << std::endl;
	std::cout << std::endl;

	animal->makeSound();
	dog->makeSound();
	cat->makeSound();
	wrongAnimal->makeSound();
	wrongCat->makeSound();
	std::cout << std::endl;

	delete animal;
	std::cout << std::endl;
	delete cat;
	std::cout << std::endl;
	delete dog;
	std::cout << std::endl;
	delete wrongAnimal;
	std::cout << std::endl;
	delete wrongCat;
	return (0);
}
