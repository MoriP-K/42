#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"

class Cat: public Animal
{
public:
	Cat();
	Cat(const Cat& copy);
	virtual ~Cat();

	Cat &operator=(const Cat &src);

	void makeSound(void) const;
};

#endif
