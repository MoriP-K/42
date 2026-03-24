#include "../inc/Animal.hpp"
#include "../inc/Dog.hpp"
#include "../inc/Cat.hpp"
#include "../inc/WrongAnimal.hpp"
#include "../inc/WrongCat.hpp"

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
	const WrongCat* wrongCat2 = new WrongCat();
	std::cout << std::endl;

	std::cout << animal->getType() << " " << std::endl;
	std::cout << dog->getType() << " " << std::endl;
	std::cout << cat->getType() << " " << std::endl;
	std::cout << wrongAnimal->getType() << " " << std::endl;
	std::cout << wrongCat->getType() << " " << std::endl;
	std::cout << wrongCat2->getType() << " " << std::endl;
	std::cout << std::endl;

	animal->makeSound();
	dog->makeSound();
	cat->makeSound();
	wrongAnimal->makeSound();
	wrongCat->makeSound();
	wrongCat2->makeSound();
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
	std::cout << std::endl;
	delete wrongCat2;
	return (0);
}
