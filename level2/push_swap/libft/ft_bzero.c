/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:17:53 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/01 20:59:11 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return ;
	ft_memset(s, 0, n);
}

// #include <stdio.h>
// #include <string.h>
// int	main()
// {
// 	// char str[10];
// 	ft_bzero(NULL, 7);
// 	// bzero(str, sizeof(str));
// 	// for (int i=0;i<10;i++)
// 	// 	printf("i = %d, value = '%c'\n", i, str[i]);
// }
