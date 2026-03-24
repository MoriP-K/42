/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:08:45 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/02 17:15:00 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	s1_p = (unsigned char *)s1;
	s2_p = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_p[i] != s2_p[i])
			return ((int)(s1_p[i] - s2_p[i]));
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char s1[] = "12345";
// 	const char s2[] = "12349";
// 	printf("c :%d\n", memcmp(s1, s2, 5));
// 	printf("my:%d\n", ft_memcmp(s1, s2, 5));
// 	return (0);
// }