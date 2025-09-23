#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

int main()
{
	std::cout << "===== Vector Test =====" << std::endl;
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	try
	{
		std::vector<int>::iterator it = easyfind(vec, 3);
		std::cout << "Found   : " << *it << std::endl;
		std::cout << "Position: " << std::distance(vec.begin(), it) << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error:" << error.what() << std::endl;
	}

	std::cout << "\n===== Exception Test =====" << std::endl;
	try
	{
		easyfind(vec, 10);
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what()  << std::endl;
	}

	std::cout << "\n===== List Test =====" << std::endl;
	std::list<int> lst;
	lst.push_back(10);
	lst.push_back(20);
	lst.push_back(30);

	try
	{
		std::list<int>::iterator it = easyfind(lst, 20);
		std::cout << "Found in list: " << *it << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what()  << std::endl;
	}

	std::cout << "\n===== Deque Test =====" << std::endl;
	std::deque<int> deq;
	deq.push_back(100);
	deq.push_back(200);
	deq.push_back(300);

	try
	{
		std::deque<int>::iterator it = easyfind(deq, 200);
		std::cout << "Found in deque: " << *it << std::endl;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what()  << std::endl;
	}

	std::cout << "\n===== First Occurrence Test =====" << std::endl;
	std::vector<int> duplicate = {1, 2, 3, 2, 4};

	try
	{
		std::vector<int>::iterator it = easyfind(duplicate, 2);
		int position = std::distance(duplicate.begin(), it);
		std::cout << "Found 2 at position: " << position << std::endl;  // 1
		std::cout << "Value: " << *it << std::endl;                      // 20
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
}
