#include "Bureaucrat.hpp"
#include "Form.hpp"

#define NL std::cout << std::endl;

void testValid()
{
	std::cout << "\n===== Valid Test =====" << std::endl;
	try
	{
		Bureaucrat admin("admin", 75);
		NL
		std::cout << "Name: " << admin.getName() << std::endl;
		NL
		std::cout << "Grade: " << admin.getGrade() << std::endl;
		NL
		std::cout << admin << std::endl;
		NL
		admin.upGrade();
		std::cout << "After upGrade:\n" << admin << std::endl;
		NL
		admin.downGrade();
		std::cout << "After downGrade:\n" << admin << std::endl;
		NL
		std::cout << "<----- Form ----->" << std::endl;
		Bureaucrat lowest;
		Bureaucrat highest("highest", 1);
		Form middle("middle", 75, 75);
		NL
		std::cout << "Name: " << middle.getName() << std::endl;
		NL
		std::cout << "Signed: " << (middle.getSigned() ? "yes" : "no") << std::endl;
		NL
		std::cout << "Grade to sign: " << middle.getGradeToSign() << std::endl;
		NL
		std::cout << "Grade to execute: " << middle.getGradeToExecute() << std::endl;
		NL
		std::cout << middle << std::endl;
		NL
		lowest.signForm(middle);
		NL
		std::cout << middle << std::endl;
		NL
		highest.signForm(middle);
		NL
		std::cout << middle << std::endl;
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testBureaucratConstructorException()
{
	std::cout << "\n===== Bureaucrat Constructor Exception Test =====" << std::endl;
	try
	{
		Bureaucrat admin("admin", 0);
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
	try
	{
		Bureaucrat admin("admin", 151);
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testFormConstructorException()
{
	std::cout << "\n===== Form Constructor Exception Test ====" << std::endl;
	try
	{
		Form invalidForm1("Invalid1", 0, 50);
		NL
	}
	catch (const std::exception &error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
	try
	{
		Form invalidForm2("Invalid2", 50, 0);
		NL
	}
	catch (const std::exception &error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
	try
	{
		Form invalidForm3("Invalid3", 200, 50);
	}
	catch (const std::exception &error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	try
	{
		Form invalidForm3("Invalid3", 50, 200);
	}
	catch (const std::exception &error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testGradeException()
{
	std::cout << "\n===== Grade Exception Test =====" << std::endl;
	try
	{
		Bureaucrat admin("admin", 1);
		NL
		std::cout << admin << std::endl;
		NL
		admin.upGrade();
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
	try
	{
		Bureaucrat admin("admin", 150);
		NL
		std::cout << admin << std::endl;
		NL
		admin.downGrade();
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testFormSigningException()
{
	std::cout << "\n===== Form Signing Exception Test =====" << std::endl;
	try
	{
		Bureaucrat lowGrade("LowGrade", 100);
		NL
		Form restrictedForm("Restricted", 25, 10);

		std::cout << "Before signing attempt:" << std::endl;
		std::cout << restrictedForm << std::endl;
		NL
		lowGrade.signForm(restrictedForm);
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
	NL
}

void testBureaucratOrthodoxCanonicalForm()
{
	std::cout << "\n===== Bureaucrat Orthodox Canonical Form Test =====" << std::endl;
	try
	{
		Bureaucrat lowest;
		NL
		std::cout << lowest << std::endl;
		NL
		Bureaucrat original("Original", 40);
		NL
		Bureaucrat copy(original);
		NL
		std::cout << "Original: " << original << std::endl;
		NL
		std::cout << "Copy: " << copy << std::endl;
		NL
		Bureaucrat assigned("Tmp", 30);
		assigned = original;
		NL
		std::cout << "Assigned: " << assigned << std::endl;
		NL
		original.upGrade();
		NL
		std::cout << "--- After original upGrade ---" << std::endl;
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
		std::cout << "Assigned: " << assigned << std::endl;
		NL
	}
	catch (std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testFormOrthodoxCanonicalForm()
{
	std::cout << "\n===== Form Orthdox Canonical Form Test =====" << std::endl;
	try
	{
		Form defaultForm;
		std::cout << defaultForm << std::endl;
		NL
		Form original("Original", 75, 50);
		NL
		Form copy(original);
		NL
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
		NL
		Form assigned("TempName", 100, 80);
		assigned = original;
		std::cout << "Assigned: " << assigned << std::endl;
		NL
		Bureaucrat signer("Signer", 50);
		NL
		signer.signForm(original);
		NL
		std::cout << "--- After signing original ---" << std::endl;
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
		std::cout << "Assigned: " << assigned << std::endl;
		NL
	}
	catch(const std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}
	NL
}

int main(void)
{
	testValid();
	testBureaucratConstructorException();
	testFormConstructorException();
	testGradeException();
	testFormSigningException();
	testBureaucratOrthodoxCanonicalForm();
	testFormOrthodoxCanonicalForm();
	return (0);
}
