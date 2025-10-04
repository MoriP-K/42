#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>

class RPN
{
private:
	
public:
	RPN(char *args);
	~RPN();

	bool isValidArg(char *arg);

	class ArgsException: public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error");
		}
	};
};

bool isOperator(char op);

#endif
