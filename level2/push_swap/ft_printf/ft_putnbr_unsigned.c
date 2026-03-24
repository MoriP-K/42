/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:50:04 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/16 13:45:10 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_unsigned(unsigned int num)
{
	char	c;
	int		length;

	length = 0;
	if (num >= 10)
		length += ft_putnbr_unsigned(num / 10);
	c = num % 10 + '0';
	length += write(1, &c, 1);
	return (length);
}
