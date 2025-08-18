#include "../inc/ShrubberyCreationForm.hpp"

const char* ShrubberyCreationForm::FileOpenExection::what(void) const throw()
{
	return "ShrubberyCreationForm: Could not open file!";
}

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyCreation", 145, 137), _target("default")
{
	std::cout << "ShrubberyCreationForm: Default constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target): AForm("ShrubberyCreation", 145, 137), _target(target)
{
	std::cout << "ShrubberyCreationForm: Constructor for " << target << " called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &copy)
	: AForm(copy), _target(copy._target)
{
	std::cout << "ShrubberyCreationForm: Copy constructor called" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "ShrubberyCreationForm: Destructor called" << std::endl;
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &src)
{
	std::cout << "ShrubberyCreationForm: Copy assignment operator called" << std::endl;
	if (this != &src)
	{
		AForm::operator=(src);
		this->_target = src._target;
	}
	return (*this);
}

const std::string &ShrubberyCreationForm::getTarget(void) const
{
	return (this->_target);
}

void ShrubberyCreationForm::executeAction(void) const
{
	std::string filename = this->_target + "_shrubbery";
	std::ofstream file(filename.c_str());

	if (!file.is_open())
		throw FileOpenExection();
	file << "       _-_" << std::endl;
    file << "    /~~   ~~\\" << std::endl;
    file << " /~~         ~~\\" << std::endl;
    file << "{               }" << std::endl;
    file << " \\  _-     -_  /" << std::endl;
    file << "   ~  \\\\ //  ~" << std::endl;
    file << "_- -   | | _- _" << std::endl;
    file << "  _ -  | |   -_" << std::endl;
    file << "      // \\\\" << std::endl;
    file << std::endl;
	file.close();
	std::cout << "ShrubberyCreationForm: ASCII trees written to " << filename << std::endl;
}


std::ostream& operator<<(std::ostream& out, const ShrubberyCreationForm& s)
{
	out << "ShrubberyCreationForm: " << s.getName()
		<< " (signed: " << (s.getSigned() ? "yes" : "no")
		<< ", grade to sign: " << s.getGradeToSign()
		<< ", grade to execute: " << s.getGradeToExecute() << ")";
	return (out);
}
