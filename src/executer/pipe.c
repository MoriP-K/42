/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:18:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 19:43:44 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_execve(t_ms *ms, t_parse *parse)
{
	if (!parse->cmd)
		return ;
	if (ms->cl->cmd_count > 0 && check_builtin_cmd(parse->cmd))
	{
		ms->exit_status = exec_built_in(ms, parse);
		return ;
	}
	execve(ms->cl->path, parse->args, ms->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fail_to_fork(t_ms *ms)
{
	throw_error("fork");
	free_ms(ms);
	exit(EXIT_FAILURE);
}

void	do_pipe(t_ms *ms, size_t index)
{
	if (ms->cl->cmd_count > 1 && index < ms->cl->cmd_count - 1)
	{
		if (pipe(ms->fd->pipe[index]) != 0)
		{
			free_ms(ms);
			throw_error(ms->parse->cmd);
			exit(EXIT_FAILURE);
		}
	}
}

void	do_child_process(t_ms *ms, t_parse *parse, size_t index)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	find_cmd(ms, parse);
	set_pipe_fds(ms, parse, ms->fd, index);
	do_execve(ms, parse);
	close_all_fds(ms->fd, parse, ms->cl->cmd_count);
	exit(EXIT_SUCCESS);
}

int	do_exec(t_ms *ms, t_parse *parse)
{
	size_t	i;
	t_parse	*current_parse;

	prepare_heredoc(ms, ms->fd, parse, parse->delimiter);
	if (is_only_builtin_cmd(ms, parse, ms->fd))
		return (1);
	current_parse = parse;
	i = 0;
	if (!current_parse || !current_parse->cmd)
		return (0);
	while (current_parse && i < ms->cl->cmd_count)
	{
		do_pipe(ms, i);
		ms->proc->id[i] = fork();
		if (ms->proc->id[i] == -1)
			fail_to_fork(ms);
		else if (ms->proc->id[i] == 0)
			do_child_process(ms, current_parse, i);
		else
			close_parent_fd(ms, ms->fd, i);
		current_parse = current_parse->next;
		i++;
	}
	return (1);
}
