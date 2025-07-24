#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal
{
protected:
	std::string _type;

public:
	AAnimal();
	AAnimal(std::string type);
	AAnimal(const AAnimal& copy);
	virtual ~AAnimal();

	AAnimal &operator=(const AAnimal &src);

	virtual void makeSound(void) const = 0;
	std::string getType() const;
};

#endif
