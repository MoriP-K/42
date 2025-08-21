#include "Bereaucrat.hpp"

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return "Bureaucrat: Grade is too high!";
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return "Bureaucrat: Grade is too low!";
}

Bureaucrat::Bureaucrat(): _name("default"), _grade(150)
{
	std::cout << "Bureaucrat: Default Constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, unsigned int grade): _name(name)
{
	std::cout << "Bureaucrat: Constructor for " << name <<" called" << std::endl;
	validateGrade(grade);
	this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy): _name(copy._name), _grade(copy._grade)
{
	std::cout << "Bureaucrat: Copy Constructor called" << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat: Destructor for " << this->_name << " called" << std::endl;
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &src)
{
	std::cout << "Bureaucrat: Copy Assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_grade = src._grade;
	}
	return (*this);
}

std::string const &Bureaucrat::getName(void) const
{
	return (this->_name);
}

unsigned int Bureaucrat::getGrade(void) const
{
	return (this->_grade);
}

void Bureaucrat::upGrade(void)
{
	std::cout << "Trying to upgrade..." << std::endl;
	if (this->_grade <= HIGHEST_GRADE)
		throw GradeTooHighException();
	this->_grade--;
}

void Bureaucrat::downGrade(void)
{
	std::cout << "Trying to downgrade..." << std::endl;
	if (this->_grade >= LOWEST_GRADE)
		throw GradeTooLowException();
	this->_grade++;
}

void Bureaucrat::validateGrade(unsigned int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bereaucrat)
{
	out << bereaucrat.getName() << ", bereaucrat grade " << bereaucrat.getGrade();
	return out;
}
