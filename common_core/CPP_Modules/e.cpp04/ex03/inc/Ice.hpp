#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice: public AMateria
{
public:
	Ice();
	Ice(const Ice& copy);
	~Ice();
	Ice &operator=(const Ice &src);

	virtual AMateria* clone() const;
	virtual void use(ICharacter& target);
};

#endif
