/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:41:12 by masa              #+#    #+#             */
/*   Updated: 2025/05/01 19:33:59 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	too_much_args_error_exit(void)
{
	write(2, "exit\n", 5);
	write(2, "minishell: too many arguments\n", 30);
}

void	print_nonnumeric_error_exit(t_ms *ms, char *arg)
{
	write(2, "exit\n", 5);
	write(2, "minishell: ", 11);
	write(2, "exit: ", 6);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
	free_ms(ms);
	exit(2);
}

void	builtin_exit(t_ms *ms, t_parse *parse)
{
	int	exit_status;

	if (parse->args[1] == NULL)
	{
		free_ms(ms);
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (!ft_isint(parse->args[1]))
		print_nonnumeric_error_exit(ms, parse->args[1]);
	else if (parse->args[2] != NULL)
	{
		too_much_args_error_exit();
		ms->exit_status = 1;
		return ;
	}
	exit_status = ft_atoi(parse->args[1]) % 256;
	free_ms(ms);
	write(1, "exit\n", 5);
	exit(exit_status);
}
