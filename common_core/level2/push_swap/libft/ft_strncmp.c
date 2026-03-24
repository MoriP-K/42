/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:19:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/03 00:15:01 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
		{
			if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
				return (1);
			else
				return (-1);
		}
		i++;
	}
	if (i < n)
	{
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		else if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		else
			return (0);
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char s1[] = "test7";
// 	const char s2[] = "test4";
// 	printf("c :%d\n", strncmp(s1, s2, 6));
// 	printf("my:%d\n", ft_strncmp(s1, s2, 6));
// 	const char s3[] = "123";
// 	const char s4[] = "1234567";
// 	printf("c :%d\n", strncmp(s3, s4, 3));
// 	printf("my:%d\n", ft_strncmp(s3, s4, 3));
// 	return (0);
// }