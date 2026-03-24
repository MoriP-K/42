/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:46:27 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/14 21:43:13 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	is_space(char c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

static int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int	ft_atoi(char *str)
{
	size_t	i;
	long	num;

	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			error_exit("input positive number!!", NULL);
		i++;
	}
	if (!is_digit(str[i]))
		error_exit("input number plzzz!!", NULL);
	num = 0;
	while (is_digit(str[i]))
	{
		if (INT_MAX < num + (str[i] - '0'))
			error_exit("input number up to INT_MAX!!", NULL);
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}
