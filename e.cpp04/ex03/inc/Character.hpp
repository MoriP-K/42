#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"
#include <string>
#include <iostream>

class Character: public ICharacter
{
public:
	static const int slot = 4;
	static const int floorSize = 100;

private: 
	std::string _name;
	AMateria* inventory[4];
	static AMateria* floor[100];
	static int floorCount;

public:
	Character();
	Character(std::string const &name);
	Character(const Character &copy);
	virtual ~Character();

	Character &operator=(const Character &src);

	virtual std::string const & getName(void) const;
	virtual void equip(AMateria* m);
	virtual void unequip(int idx);
	virtual void use(int idx, ICharacter& target);

	static void showFloor(void);
	static void cleanupFloor(void);

private:
	void clearInventory(void);
	void copyInventory(const Character &src);
	void initInventory(void);
	void dropToFloor(AMateria* m);
};

#endif
