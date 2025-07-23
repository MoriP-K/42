#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
private:
	
public:
	Brain();
	Brain(const Brain& copy);
	virtual ~Brain();

	Brain &operator=(const Brain &src);

	static const int brainMemory = 100;

protected:
	std::string ideas[brainMemory];
};

#endif
