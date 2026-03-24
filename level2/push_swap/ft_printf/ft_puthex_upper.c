/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_upper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:50:01 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/16 13:45:04 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_upper(unsigned int num)
{
	const char		upper_base[16] = "0123456789ABCDEF";
	unsigned int	hex;
	int				length;

	hex = 0;
	length = 0;
	if (num >= 16)
		length += ft_puthex_upper(num / 16);
	hex = num % 16;
	length += write(1, &upper_base[hex], 1);
	return (length);
}
