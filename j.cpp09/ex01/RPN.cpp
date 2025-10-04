#include "RPN.hpp"

RPN::RPN(char *args)
{
	if (!this->isValidArg(args))
		throw ArgsException();
}

RPN::~RPN()
{
}

bool RPN::isValidArg(char *arg)
{
	for (size_t i = 0; arg[i]; ++i)
	{
		if (isdigit(arg[i]) || isspace(arg[i]) || isOperator(arg[i]))
			continue;
		return (false);
	}
	return (true);
}

bool isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}
