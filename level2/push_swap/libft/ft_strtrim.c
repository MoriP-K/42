/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:01:53 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/04 17:08:53 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	trimmed_len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed_len = end - start;
	str = (char *)malloc(trimmed_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1 + start, trimmed_len);
	str[trimmed_len] = '\0';
	return (str);
}

// #include <stdio.h>
// int main()
// {
// 	char const str[] = "123a3241";
// 	char const set[] = "123";
// 	printf("%s\n", ft_strtrim(str, set));
// }