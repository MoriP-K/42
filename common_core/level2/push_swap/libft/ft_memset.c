/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:26:31 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/04 16:07:37 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	if (!s)
		return (NULL);
	dest = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// #include <stdio.h>
// #include <string.h>
// int	main()
// {
// 	// char str[10];
// 	ft_memset(NULL, 0, 7);
// 	// (str, sizeof(str));
// 	// for (int i=0;i<10;i++)
// 	// 	printf("i = %d, value = '%c'\n", i, str[i]);
// }

// void	f(int n, int (*arr)[n])
// {
// 	struct				list
// 	{
// 		struct list		*next;
// 		struct list		*pre;
// 		unsigned char	data[];
// 	};

// 	void				*t = __builtin_alloca(10);

// 	struct list			*el = malloc(sizeof(struct list) + sizeof(int));
// 	*((int *)el->data)
// }
