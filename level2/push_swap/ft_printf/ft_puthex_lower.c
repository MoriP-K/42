/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_lower.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:49:58 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/16 13:44:58 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_lower(unsigned int num)
{
	const char		lower_base[16] = "0123456789abcdef";
	unsigned int	hex;
	int				length;

	hex = 0;
	length = 0;
	if (num >= 16)
		length += ft_puthex_lower(num / 16);
	hex = num % 16;
	length += write(1, &lower_base[hex], 1);
	return (length);
}
