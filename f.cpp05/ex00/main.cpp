#include "Bereaucrat.hpp"

#define NL std::cout << std::endl;

void testValid()
{
	std::cout << "\n===== Valid Test =====" << std::endl;
	try
	{
		Bereaucrat admin("admin", 75);
		NL
		std::cout << "Name: " << admin.getName() << std::endl;
		NL
		std::cout << "Grade: " << admin.getGrade() << std::endl;
		NL
		std::cout << admin << std::endl;
		NL
		admin.upGrade();
		std::cout << "After upGrade: " << admin << std::endl;
		NL
		admin.downGrade();
		std::cout << "After downGade: " << admin << std::endl;
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testConstructorException()
{
	std::cout << "\n===== Constructor Exception =====" << std::endl;
	try
	{
		Bereaucrat admin("admin", 0);
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
	try
	{
		Bereaucrat admin("admin", 151);
		NL
	}
	catch (const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
	NL
}

void testGradeException()
{
	std::cout << "\n===== Grade Exception =====" << std::endl;
	try
	{
		Bereaucrat admin("admin", 1);
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
		Bereaucrat admin("admin", 150);
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

void testOrthodoxCanonicalForm()
{
	std::cout << "\n===== Orthodox Canonical Form Test =====" << std::endl;
	try
	{
		Bereaucrat def;
		NL
		std::cout << def << std::endl;
		NL
		Bereaucrat original("Original", 40);
		NL
		Bereaucrat copy(original);
		NL
		std::cout << "Original: " << original << std::endl;
		NL
		std::cout << "Copy: " << copy << std::endl;
		NL
		Bereaucrat assigned("Tmp", 30);
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

int main(void)
{
	testValid();
	testConstructorException();
	testGradeException();
	testOrthodoxCanonicalForm();
	return (0);
}
