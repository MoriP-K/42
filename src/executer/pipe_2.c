/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:42:08 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:07:08 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_built_in(t_ms *ms, t_parse *parse)
{
	if (ft_strcmp(parse->cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(parse->cmd, "cd") == 0)
		return (builtin_cd(ms, parse));
	else if (ft_strcmp(parse->cmd, "echo") == 0)
		return (builtin_echo(parse));
	else if (ft_strcmp(parse->cmd, "export") == 0)
		return (builtin_export(ms, parse));
	else if (ft_strcmp(parse->cmd, "unset") == 0)
		return (builtin_unset(ms, parse));
	else if (ft_strcmp(parse->cmd, "env") == 0)
		return (builtin_env(ms));
	else if (ft_strcmp(parse->cmd, "exit") == 0)
		builtin_exit(ms, parse);
	return (0);
}

int	is_only_builtin_cmd(t_ms *ms, t_parse *parse, t_fd *fd)
{
	if (ms->cl->cmd_count == 1 && check_builtin_cmd(parse->cmd))
	{
		if (parse->outfile)
			fd->tmp_out = ms_dup(STDOUT_FILENO, ms);
		switch_fd(ms, fd, parse, parse->token);
		ms->exit_status = exec_built_in(ms, parse);
		reset_fds(ms, fd);
		close_all_fds(fd, parse, ms->cl->cmd_count);
		return (1);
	}
	return (0);
}
