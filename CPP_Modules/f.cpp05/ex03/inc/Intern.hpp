#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"

class Intern
{
private:
	static AForm* createShrubbery(const std::string& target);
	static AForm* createRobotomy(const std::string& target);
	static AForm* createPardon(const std::string& target);

public:
	Intern();
	Intern(const Intern& copy);
	~Intern();
	Intern& operator=(const Intern& src);

	AForm* makeForm(const std::string& formName, const std::string& target);
};

#endif
