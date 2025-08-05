#include "../inc/Bereaucrat.hpp"
#include "../inc/PresidentialPardonForm.hpp"
#include "../inc/RobotomyRequestForm.hpp"
#include "../inc/ShrubberyCreationForm.hpp"

#define NL std::cout << std::endl;

// ADD: << operator implementation to all classes

void testShrubberyCreationForm(void)
{
	std::cout << "\n===== Shrubbery Creation Form Test =====" << std::endl;
	try
	{
		Bereaucrat gardener("Gardener", 140);
		Bereaucrat executor("Executor", 130);
		ShrubberyCreationForm shrub("home");

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
}

void testRobotomyRequestForm(void)
{
	std::cout << "\n===== Robotomy Request Form Test =====" << std::endl;
	try
	{
		Bereaucrat doctor("Doctor", 70);
		Bereaucrat surgeon("Surgeon", 40);
		RobotomyRequestForm robotomy("Bender");

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
	
}

void testPresidentialPardonForm(void)
{
	std::cout << "\n===== Presidential Pardon Form Test =====" << std::endl;
	try
	{
		Bereaucrat minister("Minister", 20);
		Bereaucrat president("President", 1);
		PresidentialPardonForm pardon("Arthur Dent");

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
}

void testFormExecutionExceptions(void)
{
	std::cout << "\n===== Form Execution Exception Test ====" << std::endl;
	try
	{
		Bereaucrat lowGrade("lowGrade", 150);
		ShrubberyCreationForm unsignedForm("test");

		std::cout << "\n----- Unsigned form -----" << std::endl;
		lowGrade.executeForm(unsignedForm);
		NL
		std::cout << "----- Insufficient grade -----" << std::endl;
		Bereaucrat signer("signer", 140);
		signer.signForm(unsignedForm);
		lowGrade.executeForm(unsignedForm);
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
}

void testPolymorphism(void)
{
	std::cout << "\n===== Polymorphism Test =====" << std::endl;
	try
	{
		Bereaucrat boss("Boss", 1);
		AForm* forms[] = {
			new ShrubberyCreationForm("garden"),
			new RobotomyRequestForm("C-3PO"),
			new PresidentialPardonForm("Ford Perfect")
		};
		for (int i = 0; i < 3; i++)
		{
			std::cout << "--- Processing " << forms[i]->getName() << " ---" << std::endl;
			boss.signForm(*forms[i]);
			boss.executeForm(*forms[i]);
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
