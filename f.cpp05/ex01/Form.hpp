#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bereaucrat.hpp"

class Form
{
private:
	std::string _name;
	bool isSigned;
	unsigned int sign;
	unsigned int execute;
public:
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	static const unsigned int HIGHEST_GRADE = 1;
	static const unsigned int LOWEST_GRADE = 150;

	Form();
	Form(std::string name);
	Form(const Form& copy);
	~Form();

	Form &operator=(const Form &src);

	void beSigned(Bereaucrat &bereaucrat);
};

std::ostream& operator<<(std::ostream& out, const Form& form);

#endif
