#include "Form.hpp"

const char* Form::GradeTooHighException::what(void) const throw()
{
	return "Form: Grade is too high!";
}

const char* Form::GradeTooLowException::what(void) const throw()
{
	return "Form: Grade is too low!";
}

Form::Form(): _name("DefaultForm"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "Form: Default constructor called" << std::endl;
}

Form::Form(const std::string &name, unsigned int gradeToSign, unsigned int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "Form: Constructor for " << name << " called" << std::endl;
	validateGrade(gradeToSign);
	validateGrade(gradeToExecute);
}

Form::Form(const Form &copy)
	: _name(copy._name), _isSigned(copy._isSigned), _gradeToSign(copy._gradeToSign), _gradeToExecute(copy._gradeToExecute)
{
	std::cout << "Form: Copy constructor called" << std::endl;
}

Form::~Form()
{
	std::cout << "Form: Destructor for " << this->_name << " called" << std::endl;
}

Form &Form::operator=(const Form &src)
{
	std::cout << "Form: Copy Assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_isSigned = src._isSigned;
	}
	return (*this);
}

const std::string &Form::getName(void) const
{
	return (this->_name);
}

bool Form::getSigned(void) const
{
	return (this->_isSigned);
}

unsigned int Form::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

unsigned int Form::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

void Form::beSigned(const Bereaucrat &bereaucrat)
{
	std::cout << "Form: " << this->_name << " is being checked signature by " << bereaucrat.getName() << std::endl;
	std::cout << "Bereaucrat grade: " << bereaucrat.getGrade()
			<< ", Required grade: " << this->getGradeToSign() << std::endl;
	if (bereaucrat.getGrade() > this->_gradeToSign)
		throw GradeTooLowException();
	if (this->_isSigned == true)
	{
		std::cout << "Form " << this->_name << " is already signed" << std::endl;
		return ;
	}
	this->_isSigned = true;
	std::cout << "Form: " << this->_name << " has been signed by " << bereaucrat.getName() << std::endl;
}

void Form::validateGrade(unsigned int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
	out << "Form: " << form.getName()
		<< " (signed: " << (form.getSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << ")";
	return (out);
}

