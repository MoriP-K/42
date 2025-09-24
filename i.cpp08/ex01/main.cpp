#include "Span.hpp"

int main()
{
	Span sp(5);

	sp.addNumber(4);
	sp.addNumber(2);

	std::vector<int> vec = sp.getNumbers();
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << "vec[" << i << "]: " <<  vec[i] << std::endl;
	}
	try
	{
		std::cout << "Longest Span : " << sp.longestSpan() << std::endl;
		std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error:" << error.what() << std::endl;
	}
	return 0;
}
