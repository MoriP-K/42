#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class ICharacter;

class Cure: public AMateria
{
public:
	Cure();
	Cure(const Cure& copy);
	~Cure();
	Cure &operator=(const Cure &src);

	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif

