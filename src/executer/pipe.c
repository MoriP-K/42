/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:18:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 22:24:03 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_execve(t_ms *ms, t_parse *parse)
{
	// t_parse *tmp;

	// tmp = parse;
	// write(1, "\n", 1);
	// while (tmp)
	// {
	// 	if (tmp->args)
	// 	{
	// 		int i = 0;
	// 		while (tmp->args[i])
	// 		{
	// 			printf("args[%d] :%s\n", i, tmp->args[i]);
	// 			i++;
	// 		}
	// 		write(1, "\n", 1);
	// 	}
	// 	tmp = tmp->next;
	// }
	execve(ms->cl.path, parse->args, ms->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fail_to_fork(t_ms *ms)
{
	throw_error("fork");
	(void)ms;
	// all_free();
}

void	do_pipe(t_ms *ms, size_t index)
{
	if (index < ms->cl.cmd_count - 1)
	{
		if (pipe(ms->fd.pipe[index]) != 0)
		{
			// all_free();
			throw_error(ms->parse->cmd);
		}
	}
}

void	set_pipe_fds(t_ms *ms, t_fd *fd, size_t index)
{
	// is_in_redirect();
	// is_out_redirect();
	if (ms->cl.cmd_count > 1)
	{
		if (index == 0)
		{
			if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
			{
				throw_error("dup2_a");
				// all_free();
			}
		}
		else if (index == ms->cl.cmd_count - 1)
		{
			if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
			{
				throw_error("dup2_b");
				// all_free();
			}
		}
		else
		{
			if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
			{
				throw_error("dup2_a");
				// all_free();
			}
			if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
			{
				throw_error("dup2_bb");
				// all_free();
			}
		}
	}
	close_fds(ms, &(ms->fd), index);
}

void	do_exec(t_ms *ms, t_parse *parse)
{
	size_t	i;
	t_parse	*current_parse;

	current_parse = parse;
	i = 0;
	while (i < ms->cl.cmd_count && current_parse)
	{
		do_pipe(ms, i);
		ms->proc.id[i] = fork();
		if (ms->proc.id[i] == -1)
			fail_to_fork(ms);
		else if (ms->proc.id[i] == 0)
		{
			// if (check_builtin_cmd(parse->cmd))
			// 	exec_builtin_cmd();
			find_cmd(ms, current_parse);
			set_pipe_fds(ms, &(ms->fd), i);
			close_all_fds(&(ms->fd), ms->cl.cmd_count);
			do_execve(ms, current_parse);
		}
		else
		{
			close_parent_fd(ms, &(ms->fd), i);
			current_parse = current_parse->next;
		}
		i++;
	}
}
