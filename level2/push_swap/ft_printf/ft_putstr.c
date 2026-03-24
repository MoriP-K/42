/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:49:42 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/16 13:43:17 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	if (s == NULL)
	{
		length += write(1, "(null)", 6);
		return (length);
	}
	while (s[i])
	{
		length += write(1, &s[i], 1);
		i++;
	}
	return (length);
}
