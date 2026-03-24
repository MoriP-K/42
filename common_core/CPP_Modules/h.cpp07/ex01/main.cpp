#include "iter.hpp"

void square(int &i)
{
	i *= i;
}

void to_upper(std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
		str[i] = std::toupper(str[i]);
}

int main()
{
	int len = 3;

	std::cout << "===== Test int array =====" << std::endl;
	int int_arr[] = { 2, 10, 77 };

	std::cout << "--- before ---" << std::endl;
	for (int i = 0; i < len; i++)
		std::cout << int_arr[i] << std::endl;
	
	std::cout << "\n--- after ---" << std::endl;
	::iter(int_arr, len, square);
	for (int i = 0; i < len; i++)
		std::cout << int_arr[i] << std::endl;

	std::cout << "\n===== Test string array =====" << std::endl;
	std::string str_arr[] = { "aaaa", "kmoriyam", "ppppp" };
	
	std::cout << "--- before ---" << std::endl;
	for (int i = 0; i < len; i++)
		std::cout << str_arr[i] << std::endl;
	
	std::cout << "\n--- after ---" << std::endl;
	::iter(str_arr, len, to_upper);
	for (int i = 0; i < len; i++)
		std::cout << str_arr[i] << std::endl;

	return 0;
}
