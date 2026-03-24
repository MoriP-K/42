/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:16:54 by kmoriyam          #+#    #+#             */
/*   Updated: 2024/11/02 23:06:43 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void	test(unsigned int num, char *str)
// {
// 	(void)num;
// 	if ('a' <= *str && *str <= 'z')
// 		*str = *str - ('a' - 'A');
// }

// int	main(void)
// {
// 	void	(*func)(unsigned int, char*);
// 	char str[] = "abcdefg";

// 	func = test;
// 	ft_striteri(str, func);
// 	printf("%s\n", str);
// 	return (0);
// }