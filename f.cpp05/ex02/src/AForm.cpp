#include "../inc/AForm.hpp"

const char* AForm::GradeTooHighException::what(void) const throw()
{
	return "AForm: Grade is too high!";
}

const char* AForm::GradeTooLowException::what(void) const throw()
{
	return "AForm: Grade is too low!";
}

const char* AForm::FormNotSignedException::what(void) const throw()
{
	return "AForm: Form is not signed!";
}

AForm::AForm(): _name("DefaultForm"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "AForm: Default constructor called" << std::endl;
}

AForm::AForm(const std::string &name, unsigned int gradeToSign, unsigned int gradeToExecute)
	: _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "AForm: Constructor for " << name << " called" << std::endl;
	validateGrade(gradeToSign);
	validateGrade(gradeToExecute);
}

AForm::AForm(const AForm &copy)
	: _name(copy._name), _isSigned(copy._isSigned), _gradeToSign(copy._gradeToSign), _gradeToExecute(copy._gradeToExecute)
{
	std::cout << "AForm: Copy constructor called" << std::endl;
}

AForm::~AForm()
{
	std::cout << "AForm: Destructor for " << this->_name << " called" << std::endl;
}

AForm &AForm::operator=(const AForm &src)
{
	std::cout << "AForm: Copy Assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_isSigned = src._isSigned;
	}
	return (*this);
}

const std::string &AForm::getName(void) const
{
	return (this->_name);
}

bool AForm::getSigned(void) const
{
	return (this->_isSigned);
}

unsigned int AForm::getGradeToSign(void) const
{
	return (this->_gradeToSign);
}

unsigned int AForm::getGradeToExecute(void) const
{
	return (this->_gradeToExecute);
}

void AForm::beSigned(const Bereaucrat &bereaucrat)
{
	std::cout << "AForm: " << this->_name << " is being checked signature by " << bereaucrat.getName() << std::endl;
	std::cout << "Bereaucrat grade: " << bereaucrat.getGrade()
			<< ", Required grade: " << this->getGradeToSign() << std::endl;
	if (bereaucrat.getGrade() > this->_gradeToSign)
		throw GradeTooLowException();
	if (this->_isSigned == true)
	{
		std::cout << "AForm " << this->_name << " is already signed" << std::endl;
		return ;
	}
	this->_isSigned = true;
	std::cout << "AForm: " << this->_name << " has been signed by " << bereaucrat.getName() << std::endl;
}

void AForm::execute(Bereaucrat const & executor) const
{
	if (!this->_isSigned)
		throw FormNotSignedException();
	if (executor.getGrade() > this->_gradeToExecute)
		throw GradeTooLowException();
	std::cout << "AForm: " << this->_name << " is being executed by " << executor.getName() << std::endl;
	executeAction();
}

void AForm::validateGrade(unsigned int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const AForm& form)
{
	out << "AForm: " << form.getName()
		<< " (signed: " << (form.getSigned() ? "yes" : "no")
		<< ", grade to sign: " << form.getGradeToSign()
		<< ", grade to execute: " << form.getGradeToExecute() << ")";
	return (out);
}

