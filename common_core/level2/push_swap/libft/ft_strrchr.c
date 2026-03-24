/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:13 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/02 17:00:36 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*result;
	char	*s_p;
	char	char_c;

	if (!s)
		return (NULL);
	result = NULL;
	s_p = (char *)s;
	char_c = (char)c;
	i = 0;
	while (s_p[i])
	{
		if (s[i] == char_c)
			result = &s_p[i];
		i++;
	}
	if (result)
		return (result);
	else if (char_c == '\0')
		return (&s_p[i]);
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int main()
// {
// 	char s1[] = "012345563565";

// 	printf("my: %s\n", ft_strrchr(s1, '0'));
// }