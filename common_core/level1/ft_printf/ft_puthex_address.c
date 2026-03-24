/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:49:55 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/15 22:41:10 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress(unsigned long int address)
{
	const char	hex_base[16] = "0123456789abcdef";
	long int	c_hex;
	int			length;

	length = 0;
	if (address == 0)
	{
		length += ft_putstr("(nil)");
		return (length);
	}
	if (address >= 16)
		length += ft_putaddress(address / 16);
	c_hex = address % 16;
	if (length == 0)
		length += write(1, "0x", 2);
	length += write(1, &hex_base[c_hex], 1);
	return (length);
}
