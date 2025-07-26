#ifndef BEREAUCRAT_HPP
#define BEREAUCRAT_HPP

#include <string>

class Bereaucrat
{
private:
	std::string _name;
	unsigned int grade;

public:
	Bereaucrat();
	Bereaucrat(std::string name);
	Bereaucrat(const Bereaucrat& copy);
	~Bereaucrat();

	Bereaucrat &operator=(const Bereaucrat &src);

	std::string const &getName(void) const;
	int const &getGrade(void) const;
	void upGrade(void);
	void downGrade(void);
};


#endif