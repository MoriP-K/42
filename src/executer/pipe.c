/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:18:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/01 22:57:16 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_built_in(t_ms *ms, char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(ms->parse);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo();
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export();
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env();
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit();
}

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
			if (is_redirection(ms, parse))
				
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
