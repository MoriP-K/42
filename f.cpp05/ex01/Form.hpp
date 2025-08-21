#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"
# include <exception>
# include <iostream>
# include <string>

class	Bureaucrat;

class Form
{
  private:
	const std::string _name;
	bool _isSigned;
	const unsigned int _gradeToSign;
	const unsigned int _gradeToExecute;

  public:
	class GradeTooHighException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class GradeTooLowException : public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	static const unsigned int HIGHEST_GRADE = 1;
	static const unsigned int LOWEST_GRADE = 150;

	Form();
	Form(const std::string &name, unsigned int gradeToSign,
		unsigned int gradeToExecute);
	Form(const Form &copy);
	~Form();

	Form &operator=(const Form &src);

	std::string const &getName(void) const;
	bool getSigned(void) const;
	unsigned int getGradeToSign(void) const;
	unsigned int getGradeToExecute(void) const;

	void beSigned(const Bureaucrat &bereaucrat);

  private:
	void validateGrade(unsigned int grade) const;
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
