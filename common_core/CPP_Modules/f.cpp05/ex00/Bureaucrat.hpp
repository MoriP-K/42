#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <exception>
# include <iostream>
# include <string>

class Bureaucrat
{
private:
	const std::string _name;
	unsigned int _grade;

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

	Bureaucrat();
	Bureaucrat(std::string name, unsigned int grade);
	Bureaucrat(const Bureaucrat &copy);
	~Bureaucrat();

	Bureaucrat &operator=(const Bureaucrat &src);

	std::string const &getName(void) const;
	unsigned int getGrade(void) const;

	void upGrade(void);
	void downGrade(void);

private:
	void validateGrade(unsigned int grade) const;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bereaucrat);

#endif
