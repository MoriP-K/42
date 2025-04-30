/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:44:49 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/30 17:53:06 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_executable_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

int	check_builtin_cmd(char *cmd)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	int					i;
	size_t				len;

	if (!cmd)
		return (0);
	len = ft_strlen(cmd);
	if (len == 0)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	cmd_not_found(t_ms *ms, char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_ms(ms);
	exit(127);
}

void	find_cmd(t_ms *ms, t_parse *parse)
{
	if (!parse->cmd)
		return ;
	if (ms->cl->cmd_count > 0 && check_builtin_cmd(parse->cmd))
		return ;
	else if (ft_strchr(parse->cmd, '/'))
	{
		if (is_executable_file(parse->cmd))
			ms->cl->path = parse->cmd;
		else
		{
			throw_error(parse->cmd);
			free_ms(ms);
		}
		return ;
	}
	else
	{
		ms->cl->path = find_cmd_path(parse->cmd, ms->env, ms);
		if (!ms->cl->path)
			cmd_not_found(ms, parse->cmd);
		return ;
	}
}
