#ifndef BEREAUCRAT_HPP
#define BEREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Form.hpp"

class Bereaucrat
{
private:
	std::string _name;
	unsigned int _grade;

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

	Bereaucrat();
	Bereaucrat(std::string name, unsigned int grade);
	Bereaucrat(const Bereaucrat& copy);
	~Bereaucrat();

	Bereaucrat &operator=(const Bereaucrat &src);

	std::string const &getName(void) const;
	unsigned int const &getGrade(void) const;

	void upGrade(void);
	void downGrade(void);

	void signForm(Form &form);
};

std::ostream& operator<<(std::ostream& out, const Bereaucrat& bereaucrat);

#endif
