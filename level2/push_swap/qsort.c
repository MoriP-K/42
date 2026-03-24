#include <stdio.h>
#include "libft/libft.h"

void	swap(int *x, int *y)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

int	partition(int array[], int left, int right)
{
	int	i;
	int	j;
	int	pivot;

	i = left;
	j = right + 1;
	pivot = left;
	while (1)
	{
		i++;
		while (array[pivot] > array[i])
			i++;
		j--;
		while (array[pivot] < array[j])
			j--;
		if (i >= j)
			break ;
		swap(&array[i], &array[j]);
	}
	swap(&array[pivot], &array[j]);
	return (j);
}

void	quick_sort(int array[], int left, int right)
{
	int pivot;

	if (left < right)
	{
		pivot = partition(array, left, right);
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

#include <stdlib.h>
int main()
{
	// int array[10] = { 3, 5, 7, 1, 9, 4, 8, 0, 2, 6 };
	// int i;

	// printf("Before\n");
	// i = 0;
	// while (i < 10)
	// 	printf("%d ", array[i++]);
	// printf("\n");

	// quick_sort(array, 0, 9);

	// printf("After\n");
	// i = 0;
	// while (i < 10)
	// 	printf("%d ", array[i++]);
	char str[11] = "17";
	char *endptr = NULL;
	char *ep = NULL;
	long result = strtol(str, &endptr, 10);
	long res =    ft_strtol(str, &ep);
	printf("c : %ld\n", result);
	printf("my: %ld\n", res);
	if (*endptr != '\0')
		printf("Unparsed part: %p\n", endptr);
	if (*ep != '\0')
		printf("Unparsed part: %p\n", ep);
}