/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:09:50 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/02 17:51:04 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lit_len;

	if (!big || !little)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	lit_len = ft_strlen(little);
	while ((i + lit_len <= len) && big[i])
	{
		if (little[0] == big[i])
		{
			if (ft_strncmp(&big[i], little, lit_len) == 0)
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	const char s1[] = "123456789";
// 	const char s2[] = "456";
// 	printf("my:%s\n", ft_strnstr(s1, s2, 9));
// 	return (0);
// }