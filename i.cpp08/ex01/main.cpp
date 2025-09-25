#include "Span.hpp"

int main()
{
	std::cout << "===== TEST: normal =====" << std::endl;
	try
	{
		Span sp(5);

		sp.addNumber(4);
		sp.addNumber(2);
		sp.addNumber(16);
		sp.addNumber(75);
		sp.addNumber(34);

		std::vector<int> vec = sp.getNumbers();
		std::cout << "Numbers: ";
		for (unsigned int i = 0; i < vec.size(); i++)
			std::cout <<  vec[i] << " ";
		std::cout << std::endl;
		std::cout << "Longest Span : " << sp.longestSpan() << std::endl;
		std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	std::cout << "\n===== TEST: Egde cases =====" << std::endl;
	std::cout << "--- 0 elements ---" << std::endl;
    try
    {
        Span empty(5);
        std::cout << "Longest Span : " << empty.longestSpan() << std::endl;
    }
    catch(const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

    std::cout << "\n--- 1 element ---" << std::endl;
    try
    {
        Span single(5);
        single.addNumber(42);
        std::cout << "Shortest Span: " << single.shortestSpan() << std::endl;
    }
    catch(const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

	std::cout << "\n===== TEST: Duplicate values =====" << std::endl;
    try
    {
        Span dup(4);
        dup.addNumber(5);
        dup.addNumber(5);
        dup.addNumber(10);
        dup.addNumber(5);

        std::cout << "Longest Span : " << dup.longestSpan() << std::endl;   // 10-5=5
        std::cout << "Shortest Span: " << dup.shortestSpan() << std::endl;  // 5-5=0
    }
    catch(const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

    std::cout << "\n===== TEST: Negative numbers =====" << std::endl;
    try
    {
        Span neg(4);
        neg.addNumber(-10);
        neg.addNumber(-5);
        neg.addNumber(0);
        neg.addNumber(15);
        
        std::cout << "Longest Span : " << neg.longestSpan() << std::endl;   // 15-(-10)=25
        std::cout << "Shortest Span: " << neg.shortestSpan() << std::endl;  // 0-(-5)=5
    }
    catch(const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

    std::cout << "\n===== TEST: Exception =====" << std::endl;
	std::cout << "--- container full ---" << std::endl;
	try
	{
		Span full(2);

		full.addNumber(4);
		full.addNumber(2);
		full.addNumber(42);
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	std::cout << "\n--- not enough numbers ---" << std::endl;
	try
	{
		Span notEnough(2);

		notEnough.addNumber(4);

		std::vector<int> vec = notEnough.getNumbers();

		for (unsigned int i = 0; i < vec.size(); i++)
		{
			std::cout << "vec[" << i << "]: " <<  vec[i] << std::endl;
		}

		std::cout << "Longest Span : " << notEnough.longestSpan() << std::endl;
		std::cout << "Shortest Span: " << notEnough.shortestSpan() << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

    std::cout << "\n===== TEST: Large container (10000 elements) =====" << std::endl;
    try
    {
        Span large(10000);
        
        for (int i = 0; i < 10000; i++)
        {
            large.addNumber(i * 2);  // 0, 2, 4, 6, ...
        }
        
        std::cout << "Container size: " << large.getNumbers().size() << std::endl;
        std::cout << "Longest Span : " << large.longestSpan() << std::endl;   // 19998-0=19998
        std::cout << "Shortest Span: " << large.shortestSpan() << std::endl;  // 2-0=2
    }
    catch(const std::exception& error)
    {
        std::cout << "Error: " << error.what() << std::endl;
    }

	return 0;
}
