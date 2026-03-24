/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:08:31 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/02 16:06:41 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char str[] = "123456";
// 	printf("%lu\n", ft_strlen(NULL));
// 	printf("%lu\n", strlen(str));
// }