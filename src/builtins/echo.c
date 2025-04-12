/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:05:12 by masa              #+#    #+#             */
/*   Updated: 2025/04/12 12:54:45 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_n_option(char *arg)
{
	int	i = 1;
	
	if (arg[0] != '-')
		return(0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return(0);
		i++;
	}
	return(1);
}

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
	while (parse->args[i])
	{
		if (is_n_option(parse->args[i]))
			newline = 0;
		else
			break;
		i++;
	}
	while (parse->args[i])
	{
		write(1, parse->args[i], ft_strlen(parse->args[i]));
		if (parse->args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
