#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int	ft_put_nbr(int num)
{
	char c;
	int word;

	word = 0;
	if (num < 0)
	{
		if (num == -2147483648)
		{
			word = write(1, "-2147483648", 11);
			return (word);
		}
		num = -num;
		word += write(1, "-", 1);
	}
	if (num >= 10)
		word += ft_put_nbr(num / 10);
	c = num % 10 + '0';
	word += write(1, &c, 1);
	return (word);
}

int	ft_put_str(char *str)
{
	int i;
	int word;

	i = 0;
	word = 0;
	if (!str)
	{
		word = write(1, "(null)", 6);
		return (word); 
	}
	while (str[i])
	{
		word += write(1, &str[i], 1);
		i++;
	}
	return (word);
}

int	ft_put_hex(unsigned int num)
{
	const char hex[16] = "0123456789abcdef";
	int c;
	int word;

	word = 0;
	if (num >= 16)
		word += ft_put_hex(num / 16);
	c = num % 16;
	word += write(1, &hex[c], 1);
	return (word);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int i;
	int	d;
	char *s;
	int	words;

	va_start(ap, fmt);
	i = 0;
	d = 0;
	s = NULL;
	words = 0;
	while (fmt[i])
	{
		// if (fmt[i] == '%' && fmt[i + 1] == '\0')
		// 	break ;
		if (fmt[i] == '%')
		{
			i++;
			if (fmt[i] == 'd')
			{
				d = va_arg(ap, int);
				words += ft_put_nbr(d);
			}
			else if (fmt[i] == 's')
			{
				s = va_arg(ap, char *);
				words += ft_put_str(s);
			}
			else if (fmt[i] == 'x')
			{
				d = va_arg(ap, int);
				words += ft_put_hex(d);
			}
			else
				words += write(1, &fmt[i], 1);
		}
		else
		{
			words += write(1, &fmt[i], 1);
		}
		i++;
	}
	va_end(ap);
	return (words);
}

int main()
{
	printf("c :  %d\n", printf("d = %ld\ns = %s\nx = %lx\n", -2147483648, "42 is the world!", -2147483648));
	ft_printf("my: % %d\n", ft_printf("d = %d\ns = %s\nx = %x\n", -2147483648, "42 is the world!", -2147483648));
}
