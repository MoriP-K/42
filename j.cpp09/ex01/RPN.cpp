#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(char *args)
{
	if (!this->isValidArg(args))
		throw ArgsException();
}

RPN::RPN(const RPN &copy): _input(copy._input)
{
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
	{
		this->_input = src._input;
	}
	return (*this);
}

RPN::~RPN()
{
}

void RPN::calculate(void)
{
	std::stack<int> st;

	const char *input = this->_input.c_str();
	for (size_t i = 0; input[i]; i++)
	{
		if (isspace(input[i]))
			continue;
		else if (isdigit(input[i]))
			this->_token.push(std::atoi(&input[i]));
		else if (isOperator(input[i]))
			this->execOperator(input[i]);
	}
}

void RPN::execOperator(const char op)
{
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
	int sum;

	std::cout << "\nadd" << std::endl;
	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	sum = t2 + t1;
	std::cout << "sum: " << sum << std::endl;
	this->_token.push(sum);
}

void RPN::subtract(void)
{
	int t1;
	int t2;
	int sub;

	std::cout << "\nsub" << std::endl;
	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	sub = t2 - t1;
	std::cout << "sub: " << sub << std::endl;
	this->_token.push(sub);
}

void RPN::multiply(void)
{
	int t1;
	int t2;
	int mul;

	std::cout << "\nmul" << std::endl;
	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	mul = t2 * t1;
	std::cout << "mul: " << mul << std::endl;
	this->_token.push(mul);
}

void RPN::divide(void)
{
	int t1;
	int t2;
	int div;


	std::cout << "\ndiv" << std::endl;
	t1 = this->_token.top();
	this->_token.pop();
	t2 = this->_token.top();
	this->_token.pop();
	if (t1 == 0)
		throw DivideByZeroException();
	div = t2 / t1;
	std::cout << "div: " << div << std::endl;
	this->_token.push(div);
}

bool RPN::isValidArg(char *arg)
{
	int num_count = 0;
	int ope_count = 0;

	for (size_t i = 0; arg[i]; ++i)
	{
		if (isdigit(arg[i]))
		{
			++num_count;
			continue;
		}
		else if (isspace(arg[i]))
			continue;
		else if (isOperator(arg[i]))
			++ope_count;
		else
			return (false);
	}
	if (num_count - ope_count != 1)
		return (false);
	this->_input = arg;
	return (true);
}

bool isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}
