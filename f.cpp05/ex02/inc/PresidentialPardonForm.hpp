#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm: public AForm
{
private:
    std::string _target;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(const std::string &target);
    PresidentialPardonForm(const PresidentialPardonForm &copy);
    virtual ~PresidentialPardonForm();
    PresidentialPardonForm &operator=(const PresidentialPardonForm &src);

    const std::string &getTarget() const;
    virtual void executeAction() const;
};

std::ostream& operator<<(std::ostream& out, const PresidentialPardonForm& p);

#endif
