#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "../inc/AForm.hpp"
#include <fstream>

class ShrubberyCreationForm: public AForm
{
private:
	std::string _target;

public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &copy);
	virtual ~ShrubberyCreationForm();
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &src);

	const std::string &getTarget(void) const;
	virtual void executeAction(void) const;

	class FileOpenExection: public std::exception
	{
		public:
			virtual const char* what(void) const throw();
	};
};

std::ostream& operator<<(std::ostream& out, const ShrubberyCreationForm& s);

#endif
