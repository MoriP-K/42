#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap: public ScavTrap, public FragTrap // 基底クラスのインスタンスを1つのみ作成
{
private:
	std::string _name;

public:
	DiamondTrap();
	DiamondTrap(const DiamondTrap& copy);
	DiamondTrap(std::string name);
	virtual ~DiamondTrap();

	DiamondTrap &operator=(const DiamondTrap &src);

	void attack(const std::string &target);
	void whoAmI(void);
};

#endif
