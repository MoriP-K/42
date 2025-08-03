#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardon", 25, 5), _target("default")
{
    std::cout << "PresidentialPardonForm: Default constructor called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("PresidentialPardon", 25, 5), _target(target)
{
    std::cout << "PresidentialPardonForm: Constructor for target " << target << " called" << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &copy)
    : AForm(copy), _target(copy._target)
{
    std::cout << "PresidentialPardonForm: Copy constructor called" << std::endl;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "PresidentialPardonForm: Destructor called" << std::endl;
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &src)
{
    std::cout << "PresidentialPardonForm: Copy assignment operator called" << std::endl;
    if (this != &src)
    {
        AForm::operator=(src);
        this->_target = src._target;
    }
    return (*this);
}

const std::string &PresidentialPardonForm::getTarget() const
{
    return this->_target;
}

void PresidentialPardonForm::executeAction() const
{
    std::cout << this->_target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
