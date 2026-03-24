#include <iostream>
#include <cctype>

int main(int ac, char **av)
{
	if (ac > 1)
	{
		for (int i = 1; i < ac; i++)
		{
			for (int j = 0; av[i][j]; j++)
			{
				std::cout << (unsigned char)std::toupper(av[i][j]);
			}
		}
	}
	else
	{
		std::cout << "* LOUD AND UNBREAKABLE FEEDBACK NOISE *";
	}
	std::cout << std::endl;
	return 0;
}
