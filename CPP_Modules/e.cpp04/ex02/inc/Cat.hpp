#ifndef CAT_HPP
#define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat: public AAnimal
{
private:
	Brain *brain;

public:
	Cat();
	Cat(const Cat& copy);
	virtual ~Cat();

	Cat &operator=(const Cat &src);

	void makeSound(void) const;
	Brain* getBrain(void) const;
};

#endif
