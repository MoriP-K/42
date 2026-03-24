#include "../inc/Intern.hpp"
#include "../inc/ShrubberyCreationForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/PresidentialPardonForm.hpp"

Intern::Intern()
{
	std::cout << "Intern: Default Constructor called" << std::endl;
}

Intern::Intern(const Intern& copy)
{
	(void)copy;
	std::cout << "Intern: Copy Constructor called" << std::endl;
}

Intern::~Intern()
{
	std::cout << "Intern: Destructor called" << std::endl;
}

Intern &Intern::operator=(const Intern &src)
{
	std::cout << "Intern: Copy Assignment operator called" << std::endl;
	if (this != &src)
	{
	}
	(void)src;
	return (*this);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target)
{
	std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm* (*creators[])(const std::string&) = {
		&Intern::createShrubbery,
		&Intern::createRobotomy,
		&Intern::createPardon,
	};

	for (int i = 0; i < 3; i++)
	{
		if (formNames[i] == formName)
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (*creators[i])(target);
		}
	}

	std::cout << "Error: Form '" << formName << "' does not exist" << std::endl;
	return (NULL);
}

AForm* Intern::createShrubbery(const std::string& target)
{
	return (new ShrubberyCreationForm(target));
}

AForm* Intern::createRobotomy(const std::string& target)
{
	return (new RobotomyRequestForm(target));
}

AForm* Intern::createPardon(const std::string& target)
{
	return (new PresidentialPardonForm(target));
}
