#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA: public Weapon
{
	private:
		std::string name;
		std::string type;

	public:
		HumanA();
		HumanA(std::string name, std::string type);
		~HumanA();

	private:
		void attack(void);
};

#endif
