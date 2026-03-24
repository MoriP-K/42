/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:14:17 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/15 21:49:32 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnchr(char const *str, char search)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == search)
			return (++i);
		i++;
	}
	return (0);
}
