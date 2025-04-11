/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:05:12 by masa              #+#    #+#             */
/*   Updated: 2025/04/11 01:22:57 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_parse *parse)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (parse->args == NULL || parse->args[1] == NULL)
	{
		write(1, "\n", 1);
		return;
	}
	if (parse->args[1] && string_compare(parse->args[1], "-n"))
	{
		newline = 0;
		i++;
	}
	while (parse->args[i])
	{
		write(1, parse->args[i], ft_strlen(parse->args[i]));
		if (parse->next != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
