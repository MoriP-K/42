#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie
{
	private:
		std::string name;

	public:
		Zombie();
		Zombie(const std::string& zombieName);
		~Zombie();

		void	announce(void);
		void	setName(const std::string& zombieName);
};

Zombie *newZombie(std::string name);
void	randomChump(std::string name);

#endif
