/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:28:40 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/03 00:14:48 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if ((nmemb != 0 && size != 0) && nmemb > INT_MAX / size)
		return (NULL);
	new = malloc(nmemb * size);
	if (!new)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	// const char s1[] = "123456789";
// 	// const char s2[] = "456";
// 	// char *str = (char *)calloc((size_t)(-1) / 2 - 1, 2);
// 	// char *str2 = (char *)ft_calloc(10, -5);
// 	// // printf("c :%s\n", str);
// 	// printf("my:%lu\n", strlen(str2));
// 	// // free(str);
// 	// free(str2);
// 	char *s;
// 	s = malloc(0);
// 	printf("%p", s);
// 	free(s);
// 	return (0);
// }
