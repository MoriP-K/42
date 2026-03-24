/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:05:09 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/12/15 15:13:51 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t		i;
	int			sign;
	long int	result;

	i = 0;
	while (('\t' <= nptr[i] && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	result = 0;
	while (ft_isdigit((int)nptr[i]))
	{
		if (sign == 1 && result > (LONG_MAX - (nptr[i] - '0')) / 10)
			return ((int)LONG_MAX);
		else if (sign == -1 && result > (LONG_MAX - (nptr[i] - '0')) / 10)
			return ((int)LONG_MIN);
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return ((int)(sign * result));
}

// #include <stdio.h>
// #include <stdlib.h>
// int main()
// {
// 	// printf("c :%d\n",ft_atoi((char *)NULL));
// 	printf("c :%d\n",atoi("9223372036854775809"));
// 	printf("my:%d\n",ft_atoi("9223372036854775809"));

// 	printf("c :%d\n",atoi("-2147483648"));
// 	printf("my:%d\n",ft_atoi("-2147483648"));

// 	printf("c :%d\n",atoi("-9223372036854775808"));
// 	printf("my:%d\n",ft_atoi("-9223372036854775808"));

// 	printf("c :%d\n",atoi("\t\n\r\v\f  469 \n"));
// 	printf("my:%d\n",ft_atoi("\t\n\r\v\f  469 \n"));
// 	printf("c :%d\n",atoi("\n\n\n  -46\b9 \n5d6"));
// 	printf("my:%d\n",ft_atoi("\n\n\n  -46\b9 \n5d6"));
// 	return (0);
// }
