// float	ft_avg(int num, ...)
// {
// 	va_list	list;
// 	float	sum;

// 	va_start(list, num);
// 	sum = 0;
// 	for (int i = 0; i < num; i++)
// 		sum = sum + va_copy(list, va_arg(list, int));
// 	va_end(list);
// 	return (sum / num);
// }
// void	func(char *arg1, ...)
// {
// 	va_list	ap;

// 	va_start(ap, arg1);
// 	printf("arg2: %d\n", va_arg(ap, int));
// 	printf("arg3: %lf\n", va_arg(ap, double));
// 	va_end(ap);
// }

// #include <stdio.h>
// #include <stdarg.h>
// int	main(void)
// {
// 	char	base[16] = "123456789abcdefg";
// 	ft_printf("%%,%s", 'K', "MORIP");
// 	// printf("%f\n", ft_avg(1, 2, 3, 4, 5));
// 	// printf("\n");
// 	// func("aaaa", 5, 3.14);
// 	// ft_printf("%s, %c, %d\n", "abc", 'K', 426);
// 	// ft_printf("%s", "MORIP");
// 	// printf("%s, %c, %d\n", "abc", 'K', 426);
// }