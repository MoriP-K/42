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

#include <vector>
std::vector<int> _arr = {1, 14, 32, 51, 51, 51, 243, 419, 750, 910};

bool isOK(int index, int key);

int binarySearch(int key)
{
	int ng = -1;
	int ok = (int)_arr.size();

	while (abs(ok - ng) > 1)
	{
		int mid = (ok + ng) / 2;

		if (isOK(mid, key))
			ok = mid;
		else
			ng = ok;
	}
	return (ok);
}

bool isOK(int index, int key)
{
	if (_arr[index] >= key)
		return (true);
	return (false);
}
int	main(int ac, char const *av[])
{
	if (ac < 2 || !av[1])
		return (1);
	if (ac == 2)
		;

	// bubbleSort(av);
	// std::cout << binary_search(0) << std::endl;
	std::cout << "Index: " << binarySearch(std::atoi(av[1])) << std::endl;
	return (0);
}
