/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:48:02 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/04 16:30:35 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_p;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	s_p = (unsigned char *)s;
	while (i < n)
	{
		if (s_p[i] == (unsigned char)c)
			return ((void *)&s_p[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char s1[] = "12345";
// 	printf("c :%s\n", (char *)memchr(s1, '3', 6));
// 	printf("my:%s\n", (char *)ft_memchr(s1, '3', 6));
// 	return (0);
// }