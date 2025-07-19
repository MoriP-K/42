#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal
{
private:
	
public:
	Animal();
	Animal(const Animal& copy);
	virtual ~Animal();

	Animal &operator=(const Animal &src);

	std::string getType();

protected:
	std::string type;

	virtual void makeSound(void);
};

#endif
