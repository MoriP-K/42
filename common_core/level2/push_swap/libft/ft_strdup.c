/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:29:18 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/03 14:35:58 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char			*dup;
	unsigned int	s_len;
	unsigned int	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	dup = (char *)malloc(s_len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// int	main(void)
// {
// 	const char s1[] = "123456789";
// 	char *str = strdup(s1);
// 	char *str2 = ft_strdup(s1);
// 	printf("c :%s\n", str);
// 	printf("my:%s\n", str2);
// 	free(str);
// 	free(str2);
// 	return (0);
// }