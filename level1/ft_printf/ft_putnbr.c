/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:50:07 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/16 13:45:18 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int num)
{
	char	c;
	int		length;

	length = 0;
	if (num < 0)
	{
		if (num == -2147483648)
		{
			length += write(1, "-2147483648", 11);
			return (length);
		}
		length += write(1, "-", 1);
		num = -num;
	}
	if (num >= 10)
		length += ft_putnbr(num / 10);
	c = num % 10 + '0';
	length += write(1, &c, 1);
	return (length);
}
