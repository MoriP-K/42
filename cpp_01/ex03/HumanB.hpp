#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB: public Weapon
{
	private:
		std::string type;
		std::string name;

	public:
		HumanB();
		HumanB(std::string name, std::string type);
		~HumanB();

	private:
		void attack(void);
};

#endif
