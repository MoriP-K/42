/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:46:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/15 23:29:16 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_specifier(va_list list, const char c)
{
	int		result;

	result = 0;
	if (c == 'c')
		result = ft_putchr(va_arg(list, int));
	else if (c == 's')
		result = ft_putstr(va_arg(list, char *));
	else if (c == 'p')
		result = ft_putaddress((unsigned long)va_arg(list, void *));
	else if (c == 'd' || c == 'i')
		result = ft_putnbr(va_arg(list, int));
	else if (c == 'u')
		result = ft_putnbr_unsigned(va_arg(list, unsigned int));
	else if (c == 'x')
		result = ft_puthex_lower(va_arg(list, int));
	else if (c == 'X')
		result = ft_puthex_upper(va_arg(list, int));
	else
		result = ft_putchr(c);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	size_t	i;
	int		length;

	if (format == NULL)
		return (-1);
	va_start(list, format);
	i = 0;
	length = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			length += ft_check_specifier(list, format[i]);
		}
		else
			length += ft_putchr(format[i]);
		i++;
	}
	va_end(list);
	return (length);
}

// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>
// #include <limits.h>

// int	main(void)
// {
// 	// char
// 	printf("c : c = %c\n", 'K');
// 	ft_printf("my: c = %c\n", 'K');
// 	printf("\n");

// 	// string
// 	printf("c : s = %s\n", "MoriP");
// 	ft_printf("my: s = %s\n", "MoriP");
// 	printf(" NULL %s NULL \n", (char *)NULL);
// 	ft_printf(" NULL %s NULL \n", (char *)NULL);
// 	printf("%s\n", (char *)0);
// 	ft_printf("%s\n", (char *)0);
// 	printf("\n");

// 	// pointer
// 	void *ptr = NULL;
// 	printf("c : *p = %p, %p\n", (int *)LONG_MIN, (int *)LONG_MAX);
// 	ft_printf("my: *p = %p, %p\n", (int *)LONG_MIN, (int *)LONG_MAX);
// 	printf("c : *p = %p\n", NULL);
// 	ft_printf("my: *p = %p\n", NULL);
// 	printf("c : *p = %p, %p\n", (int *)LONG_MIN, (int *)LONG_MAX);
// 	ft_printf("my: *p = %p, %p\n", (int *)LONG_MIN, (int *)LONG_MAX);
// 	printf("c : *p = %p, %p\n", (int *)ULONG_MAX, (int *)-ULONG_MAX);
// 	ft_printf("my: *p = %p, %p\n", (int *)ULONG_MAX,(int *) -ULONG_MAX);
// 	printf("c : *p = %p\n", (void *)0);
// 	ft_printf("my: *p = %p\n", (void *)0);
// 	printf("\n");

// 	// decimal
// 	printf("c : d = %d\n", 123456);
// 	ft_printf("my: d = %d\n", 123456);
// 	printf("\n");

// 	// integer
// 	printf("c : i = %i\n", 0);
// 	ft_printf("my: i = %i\n", 0);
// 	printf("\n");

// 	// unsigned int
// 	printf("c : u = %u\n", -456);
// 	ft_printf("my: u = %u\n", -456);
// 	printf("\n");

// 	// small x
// 	printf("c : x = %x\n", 0x12);
// 	ft_printf("my: x = %x\n", 0x12);
// 	printf("c : x = %x\n", 0);
// 	ft_printf("my: x = %x\n", 0);
// 	printf("\n");

// 	// big X
// 	printf("c : X = %X\n", 0x12);
// 	ft_printf("my: X = %X\n", 0x12);
// 	printf("c : X = %X\n", 0);
// 	ft_printf("my: X = %X\n", 0);
// 	printf("\n");

// 	// print %
// 	printf("c : %%\n");
// 	ft_printf("my: %%\n");
// 	printf("\n");

// 	// word count
// 	printf("c : word count = %i\n",
// 		printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
// 			'c', "String", ptr, 456, -987654321, 2147483647, 321, 321));
// 	ft_printf("my: word count = %i\n",
// 		ft_printf("c : %c, %s, %p, %d, %i, %u, %x, %X, %%\n",
// 			'c', "String", ptr, 456, -987654321, 2147483647, 321, 321));
// 	printf("\n");

// 	printf("%d % d\n", printf(NULL), ft_printf(NULL));
// }