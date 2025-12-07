#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(char *args)
{
	if (!this->isValidArg(args))
		throw ArgsException();
}

RPN::RPN(const RPN &copy)
{
	*this = copy;
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
	{
		this->_input = src._input;
		this->_token = src._token;
	}
	return (*this);
}

RPN::~RPN()
{
}

void RPN::calculate(void)
{
	for (size_t i = 0; this->_input[i]; i++)
	{
		if (isspace(this->_input[i]))
			continue;
		else if (isdigit(this->_input[i]))
			this->_token.push(this->_input[i] - '0');
		else if (isOperator(this->_input[i]))
			this->execOperator(this->_input[i]);
		else
			throw ArgsException();
	}
	if (this->_token.size() != 1)
		throw ArgsException();
	std::cout << this->_token.top() << std::endl;
}

void RPN::execOperator(const char op)
{
	if (this->_token.size() < 2)
		throw ArgsException();
	if (op == '+')
		this->add();
	else if (op == '-')
		this->subtract();
	else if (op == '*')
		this->multiply();
	else if (op == '/')
		this->divide();
}

void RPN::add(void)
{
	int t1;
	int t2;

	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	if (t1 > 0 && t2 > 0 && t2 > std::numeric_limits<int>::max() - t1)
		throw OverflowException();
	if (t1 < 0 && t2 < 0 && t2 < std::numeric_limits<int>::min() - t1)
		throw OverflowException();
	this->_token.push(t2 + t1);
}

void RPN::subtract(void)
{
	int t1;
	int t2;

	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	if (t1 < 0 && t2 > 0)
	{
		if (t1 == std::numeric_limits<int>::min())
			throw OverflowException();
		if (t2 > std::numeric_limits<int>::max() - (-t1))
			throw OverflowException();
	}
	if (t1 > 0 && t2 < 0)
	{
		if (t2 < std::numeric_limits<int>::min() + t1)
			throw OverflowException();
	}
	this->_token.push(t2 - t1);
}

void RPN::multiply(void)
{
	int t1;
	int t2;

	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	if (t1 != 0 && t2 != 0)
	{
		if (t1 > 0 && t2 > 0 && t2 > std::numeric_limits<int>::max() / t1)
			throw OverflowException();
		if (t1 < 0 && t2 < 0 && t2 < std::numeric_limits<int>::max() / t1)
			throw OverflowException();
		if (t1 > 0 && t2 < 0 && t2 < std::numeric_limits<int>::min() / t1)
			throw OverflowException();
		if (t1 < 0 && t2 > 0 && t2 > std::numeric_limits<int>::min() / t1)
			throw OverflowException();
	}
	this->_token.push(t2 * t1);
}

void RPN::divide(void)
{
	int t1;
	int t2;

	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	if (t1 == 0)
		throw DivideByZeroException();
	if (t2 == std::numeric_limits<int>::min() && t1 == -1)
		throw OverflowException();
	this->_token.push(t2 / t1);
}

bool RPN::isValidArg(char *arg)
{
	for (size_t i = 0; arg[i]; ++i)
	{
		if (isdigit(arg[i]))
		{
			if (arg[i + 1] && !isspace(arg[i + 1]))
				return (false);
			continue;
		}
		else if (isspace(arg[i]))
			continue;
		else if (isOperator(arg[i]))
		{
			if (arg[i + 1] && !isspace(arg[i + 1]))
				return (false);
			continue;
		}
		else
			return (false);
	}
	this->_input = arg;
	return (true);
}

bool isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}
