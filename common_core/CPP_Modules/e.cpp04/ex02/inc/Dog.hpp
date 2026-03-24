#ifndef DOG_HPP
#define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog: public AAnimal
{
private:
	Brain *brain;

public:
	Dog();
	Dog(const Dog& copy);
	virtual ~Dog();

	Dog &operator=(const Dog &src);

	void makeSound(void) const;
	Brain* getBrain(void) const;
};

#endif
