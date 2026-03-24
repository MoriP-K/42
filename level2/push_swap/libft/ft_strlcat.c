/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:40:21 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/04 17:08:44 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	max_len;
	size_t	i;

	dst_len = ft_strlen((const char *)dst);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	if (size <= dst_len)
		return (size + src_len);
	max_len = size - dst_len;
	i = 0;
	while (src[i] && i < max_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

// #include <string.h>
// #include <stdio.h>

// int main()
// {
// 	char s1[9] = "1234";
// 	char s2[] = "5678";

// 	printf("my: %zu, %s\n", ft_strlcat(s1, s2, 10), s1);
// }
