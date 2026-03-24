#include "Array.hpp"

int main()
{
	std::cout << "===== Test: size() =====" << std::endl;
	Array<int> empty;
	std::cout << "Empty size: " << empty.size() << std::endl;

	Array<int> arr(5);
	std::cout << "Array size: " << arr.size() << std::endl;

	std::cout << "\n===== Test: copy =====" << std::endl;
	arr[0] = 42;
	arr[1] = 24;
	std::cout << "arr[0]: " << arr[0] << std::endl;

	Array<int> copy(arr);
	copy[0] = 100;
	std::cout << "Original: " << arr[0] << std::endl;
	std::cout << "Copy    : " << copy[0] << std::endl;

	Array<int> assinged;
	assinged = arr;
	assinged[0] = 200;
	std::cout << "Original: " << arr[0] << std::endl;
	std::cout << "Assinged: " << assinged[0] << std::endl;

	std::cout << "\n===== Test: Exeption =====" << std::endl;
	try
	{
		arr[10] = 999;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	std::cout << "\n===== Test: string type =====" << std::endl;

	Array<std::string> strArr(2);
	strArr[0] = "Hello";
	strArr[1] = "42";
	Array<std::string> copyArr(strArr);
	copyArr[1] = "kmoriyam";

	std::cout << "Str array size: " << strArr.size() << std::endl;
	std::cout << "Original: " << strArr[0] << " " << strArr[1] << std::endl;
	std::cout << "Copy    : " << copyArr[0] << " " << copyArr[1] << std::endl;


	std::cout << "\n===== Test: Exeption =====" << std::endl;
	std::cout << "--- int ---" << std::endl;
	try
	{
		arr[10] = 999;
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}

	std::cout << "\n--- string ---" << std::endl;
	try
	{
		strArr[10] = "out of range";
	}
	catch(const std::exception& error)
	{
		std::cout << "Error: " << error.what() << std::endl;
	}
}
