#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>

class RPN
{
private:
	std::string _input;
	std::stack<int> _token;

public:
	RPN();
	RPN(char *args);
	RPN(const RPN &copy);
	RPN &operator=(const RPN &src);
	~RPN();

	bool isValidArg(char *arg);
	void calculate(void);
	void execOperator(const char op);
	void add(void);
	void subtract(void);
	void multiply(void);
	void divide(void);

	class ArgsException: public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error");
		}
	};

	class DivideByZeroException: public std::exception
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
