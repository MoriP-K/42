#include "../inc/Bureaucrat.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"

#define NL std::cout << std::endl;

void testShrubberyCreationForm(void)
{
	std::cout << "\n===== Shrubbery Creation Form Test =====" << std::endl;
	try
	{
		Bureaucrat gardener("Gardener", 140);
		NL
		Bureaucrat executor("Executor", 130);
		NL
		ShrubberyCreationForm shrub("home");
		NL

		std::cout << shrub << std::endl;
		NL
		gardener.signForm(shrub);
		std::cout << shrub << std::endl;
		NL
		executor.executeForm(shrub);
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testRobotomyRequestForm(void)
{
	std::cout << "\n===== Robotomy Request Form Test =====" << std::endl;
	try
	{
		Bureaucrat doctor("Doctor", 70);
		NL
		Bureaucrat surgeon("Surgeon", 40);
		NL
		RobotomyRequestForm robotomy("Bender");
		NL

		std::cout << robotomy << std::endl;
		NL
		doctor.signForm(robotomy);
		std::cout << robotomy << std::endl;
		NL
		for (int i = 0; i < 3; i++)
		{
			std::cout << "Attempt " << (i + 1) << ":" << std::endl;
			surgeon.executeForm(robotomy);
			NL
		}
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << '\n';
	}
	NL
}

void testPresidentialPardonForm(void)
{
	std::cout << "\n===== Presidential Pardon Form Test =====" << std::endl;
	try
	{
		Bureaucrat minister("Minister", 20);
		NL
		Bureaucrat president("President", 1);
		NL
		PresidentialPardonForm pardon("Arthur Dent");
		NL

		std::cout << pardon << std::endl;
		NL
		minister.signForm(pardon);
		std::cout << pardon << std::endl;
		NL
		president.executeForm(pardon);
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testFormExecutionExceptions(void)
{
	std::cout << "\n===== Form Execution Exception Test ====" << std::endl;
	try
	{
		Bureaucrat lowGrade("lowGrade", 150);
		NL
		ShrubberyCreationForm unsignedForm("test");
		NL

		std::cout << "\n----- Unsigned form -----" << std::endl;
		lowGrade.executeForm(unsignedForm);
		NL
		std::cout << "----- Insufficient grade -----" << std::endl;
		Bureaucrat signer("signer", 140);
		NL
		signer.signForm(unsignedForm);
		NL
		lowGrade.executeForm(unsignedForm);
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testPolymorphism(void)
{
	std::cout << "\n===== Polymorphism Test =====" << std::endl;
	try
	{
		Bureaucrat boss("Boss", 1);
		NL
		AForm* forms[] = {
			new ShrubberyCreationForm("garden"),
			new RobotomyRequestForm("C-3PO"),
			new PresidentialPardonForm("Ford Perfect")
		};
		NL
		for (int i = 0; i < 3; i++)
		{
			std::cout << "--- Processing " << forms[i]->getName() << " ---" << std::endl;
			boss.signForm(*forms[i]);
			NL
			boss.executeForm(*forms[i]);
			NL
			std::cout << *forms[i] << std::endl;
			NL
		}
		for (int i = 0; i < 3; i++)
			delete forms[i];
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

int main(void)
{
	testShrubberyCreationForm();
	testRobotomyRequestForm();
	testPresidentialPardonForm();
	testFormExecutionExceptions();
	testPolymorphism();
	return 0;
}
