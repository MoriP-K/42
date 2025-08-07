#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bereaucrat.hpp"

class Bereaucrat;

class AForm
{
private:
	const std::string _name;
	bool _isSigned;
	const unsigned int _gradeToSign;
	const unsigned int _gradeToExecute;

public:
	static const unsigned int HIGHEST_GRADE = 1;
	static const unsigned int LOWEST_GRADE = 150;

	AForm();
	AForm(const std::string &name, unsigned int gradeToSign, unsigned int gradeToExecute);
	AForm(const AForm& copy);
	virtual ~AForm();
	AForm &operator=(const AForm &src);

	std::string const &getName(void) const;
	bool getSigned(void) const;
	unsigned int getGradeToSign(void) const;
	unsigned int getGradeToExecute(void) const;

	void beSigned(const Bereaucrat &bereaucrat);
	void execute(Bereaucrat const & executor) const;

	virtual void executeAction(void) const = 0;

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

	class FormNotSignedException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

private:
	void validateGrade(unsigned int grade) const;
};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
