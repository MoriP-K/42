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

std::vector<int> arr = {1, 14, 32, 51, 51, 51, 243, 419, 750, 910};

int binary_search(int key)
{
	int left = 0; // index for begin
	int right = (int)arr.size() - 1; // index for end

	while (right >= left)
	{
		int mid = left + (right - left) / 2; // center of list
		if (arr[mid] == key)
			return (mid);
		else if (arr[mid] > key)
			right = mid - 1;
		else if (arr[mid] < key)
			left = mid + 1;
	}
	return (-1);
}

int	main(int ac, char const *av[])
{
	if (ac < 2 || !av[1])
		return (1);
	if (ac == 2)
		;

	// bubbleSort(av);
	std::cout << binary_search(0) << std::endl;
	return (0);
}
