#include "Bereaucrat.hpp"

const char* Bereaucrat::GradeTooHighException::what(void) const throw()
{
	return "Bereaucrat: Grade is too high!";
}

const char* Bereaucrat::GradeTooLowException::what(void) const throw()
{
	return "Bereaucrat: Grade is too low!";
}

Bereaucrat::Bereaucrat(): _name("default"), _grade(150)
{
	std::cout << "Bereaucrat: Default Constructor called" << std::endl;
}

Bereaucrat::Bereaucrat(std::string name, unsigned int grade): _name(name)
{
	std::cout << "Bereaucrat: Constructor for " << name <<" called" << std::endl;
	validateGrade(grade);
	this->_grade = grade;
}

Bereaucrat::Bereaucrat(const Bereaucrat& copy): _name(copy._name), _grade(copy._grade)
{
	std::cout << "Bereaucrat: Copy Constructor called" << std::endl;
}

Bereaucrat::~Bereaucrat()
{
	std::cout << "Bereaucrat: Destructor for " << this->_name << " called" << std::endl;
}

Bereaucrat &Bereaucrat::operator=(const Bereaucrat &src)
{
	std::cout << "Bereaucrat: Copy Assignment operator called" << std::endl;
	if (this != &src)
	{
		this->_grade = src._grade;
	}
	return (*this);
}

std::string const &Bereaucrat::getName(void) const
{
	return (this->_name);
}

unsigned int Bereaucrat::getGrade(void) const
{
	return (this->_grade);
}

void Bereaucrat::upGrade(void)
{
	std::cout << "Trying to upgrade..." << std::endl;
	if (this->_grade <= HIGHEST_GRADE)
		throw GradeTooHighException();
	this->_grade--;
}

void Bereaucrat::downGrade(void)
{
	std::cout << "Trying to downgrade..." << std::endl;
	if (this->_grade >= LOWEST_GRADE)
		throw GradeTooLowException();
	this->_grade++;
}

void Bereaucrat::validateGrade(unsigned int grade) const
{
	if (grade < HIGHEST_GRADE)
		throw GradeTooHighException();
	if (grade > LOWEST_GRADE)
		throw GradeTooLowException();
}

std::ostream& operator<<(std::ostream& out, const Bereaucrat& bereaucrat)
{
	out << bereaucrat.getName() << ", bereaucrat grade " << bereaucrat.getGrade();
	return out;
}
