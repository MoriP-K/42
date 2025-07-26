#include "../inc/AMateria.hpp"
#include "../inc/Character.hpp"
#include "../inc/Cure.hpp"
#include "../inc/Ice.hpp"
#include "../inc/ICharacter.hpp"
#include "../inc/IMateriaSource.hpp"
#include "../inc/MateriaSource.hpp"

#define NL std::cout << std::endl;

int main(void)
{
	IMateriaSource* src = new MateriaSource();
	NL
	src->learnMateria(new Ice());
	NL
	src->learnMateria(new Cure());
	NL
	src->learnMateria(new Ice());
	NL
	src->learnMateria(new Cure());
	NL
	src->learnMateria(new Ice());
	NL

	ICharacter* me = new Character("me");
	NL

	AMateria* tmp;
	tmp = src->createMateria("ice");
	NL
	me->equip(tmp);
	NL
	tmp = src->createMateria("cure");
	NL
	me->equip(tmp);
	NL
	tmp = src->createMateria("ice");
	NL
	me->equip(tmp);
	NL
	tmp = src->createMateria("cure");
	NL
	me->equip(tmp);
	NL
	// failed
	tmp = src->createMateria("cure");
	NL
	me->equip(tmp);
	NL
	AMateria* nullp = NULL;
	NL
	me->equip(nullp);
	NL
	me->unequip(3);
	NL
	me->unequip(3);
	NL
	me->unequip(4);
	NL
	Character::showFloor();
	NL

	ICharacter* bob = new Character("bob");
	NL

	me->use(0, *bob);
	NL
	me->use(1, *bob);
	NL

	delete bob;
	NL
	delete me;
	NL
	delete src;

	Character::cleanupFloor();

	return 0;
}
