/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 22:39:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/16 22:44:44 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *str, char *text)
{
	int	i;

	if (!str && !text)
		return (0);
	if (!str)
		return (-1);
	if (!text)
		return (1);
	i = 0;
	while (str[i] && text[i])
	{
		if (str[i] != text[i])
			return (str[i] - text[i]);
		i++;
	}
	return (str[i] - text[i]);
}
