#include <algorithm>
#include <iostream>
#include <vector>

void bubbleSort(const char **av)
{
	std::vector<int> num;
	std::cout << "Bubble sort\nBefore: ";
	for (size_t i = 1; av[i]; ++i)
	{
		num.push_back(std::atoi(av[i]));
		std::cout << num[i - 1] << ", ";
	}
	std::cout << "\n\nAfter: ";
	for (size_t i = 0; i < num.size() - 1; ++i)
	{
		for (size_t j = 0; j < num.size() - 1 - i; ++j)
		{
			if (num[j] > num[j + 1])
			{
				int tmp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = tmp;
			}
		}
	}
	for (size_t i = 0; i < num.size(); ++i)
	{
		std::cout << num[i] << ", ";
	}
}

int	main(int ac, char const *av[])
{
	if (ac < 2 || !av[1])
		return (1);
	if (ac == 2)
		;

	bubbleSort(av);
	return (0);
}
