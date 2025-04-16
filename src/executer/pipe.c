/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:18:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/16 00:01:27 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_built_in(t_ms *ms, t_parse *parse)
{
	if (ft_strcmp(parse->cmd, "pwd") == 0)
		return(builtin_pwd());
	else if (ft_strcmp(parse->cmd, "cd") == 0)
		return(builtin_cd(ms, parse));
	else if (ft_strcmp(parse->cmd, "echo") == 0)
		return(builtin_echo(parse));
	else if (ft_strcmp(parse->cmd, "export") == 0)
		return(builtin_export(ms, parse));
	else if (ft_strcmp(parse->cmd, "unset") == 0)
		return(builtin_unset(ms, parse));
	else if (ft_strcmp(parse->cmd, "env") == 0)
		return(builtin_env(ms));
	else if (ft_strcmp(parse->cmd, "exit") == 0)
		builtin_exit(ms, parse);
	return (0);
}

void	do_execve(t_ms *ms, t_parse *parse)
{
	if (check_builtin_cmd(parse->cmd))
	{
		ms->exit_status = exec_built_in(ms, parse);
		return;
	}
	execve(ms->cl.path, parse->args, ms->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	fail_to_fork(t_ms *ms)
{
	throw_error("fork");
	free_ms(ms);
}

void	do_pipe(t_ms *ms, size_t index)
{
	if (index < ms->cl.cmd_count - 1)
	{
		if (pipe(ms->fd.pipe[index]) != 0)
		{
			free_ms(ms);
			throw_error(ms->parse->cmd);
		}
	}
}

void	switch_fd(t_ms *ms, t_fd *fd, char *infile, char *outfile)
{
	if (infile)
	{
		fd->infile = open(infile, O_RDONLY);
		if (fd->infile < 0)
		{
			throw_error("open infile");
			free_ms(ms);
		}
		if (dup2(fd->infile, STDIN_FILENO) == -1)
		{
			throw_error("dup2 infile");
			free_ms(ms);
		}
	}
	if (outfile)
	{
		if (ms->parse->append)
			fd->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->outfile < 0)
		{
			throw_error("open outfile error");
			free_ms(ms);
		}
		if (dup2(fd->outfile, STDOUT_FILENO) == -1)
		{
			throw_error("dup2 outfile");
			free_ms(ms);
		}
	}
}

void	set_pipe_fds(t_ms *ms, t_parse *parse, t_fd *fd, size_t index)
{
	if (index == 0)
	{
		if (parse->infile || parse->outfile)
			switch_fd(ms, fd, parse->infile, parse->outfile);
		if (ms->cl.cmd_count != 1)
		{
			if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
			{
				throw_error("dup2_a");
				free_ms(ms);
			}
			fd->tmp_in = fd->pipe[index][1];
		}
	}
	else if (index == ms->cl.cmd_count - 1)
	{
		if (parse->infile || parse->outfile)
			switch_fd(ms, fd, parse->infile, parse->outfile);
		if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
		{
			throw_error("dup2_b");
			free_ms(ms);
		}
		fd->tmp_out = fd->pipe[index - 1][0];
	}
	else
	{
		if (parse->infile || parse->outfile)
			switch_fd(ms, fd, parse->infile, parse->outfile);
		if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
		{
			throw_error("dup2_aa");
			free_ms(ms);
		}
		fd->tmp_in = fd->pipe[index - 1][0];
		if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
		{
			throw_error("dup2_bb");
			free_ms(ms);
		}
		fd->tmp_out = fd->pipe[index][1];
	}
	close_fds(ms, &(ms->fd), index);
}

void	reset_fds(t_ms *ms , t_fd *fd)
{
	if (fd->tmp_in >= 0)
	{
		// dprintf(2, "tmp_in: %d, STDIN: %d\n", fd->tmp_in, STDIN_FILENO);
		if (dup2(fd->tmp_in, STDIN_FILENO) == -1)
		{
			throw_error("dup2 infile");
			free_ms(ms);
		}
		close(fd->tmp_in);
		fd->tmp_in = -1;
	}
	if (fd->tmp_out >= 0)
	{
		// dprintf(2, "tmp_out: %d, STDOUT: %d\n", fd->tmp_out, STDOUT_FILENO);
		if (dup2(fd->tmp_out, STDOUT_FILENO) == -1)
		{
			throw_error("reset dup2 outfile");
			free_ms(ms);
		}
		close(fd->tmp_out);
		fd->tmp_out = -1;
	}
}

int	is_only_builtin_cmd(t_ms *ms, t_parse *parse, t_fd *fd)
{
	(void)fd;
	if (ms->cl.cmd_count == 1 && check_builtin_cmd(parse->cmd))
	{
		// write(1, "builtin\n", 8);
		// if (parse->infile)
		// {
		// 	fd->tmp_in = dup(STDIN_FILENO);
		// 	if (fd->tmp_in == -1)
		// 	{
		// 		throw_error("dup");
		// 		free_ms(ms);
		// 		exit(EXIT_FAILURE);
		// 	}
		// }
		if (parse->outfile)
		{
			fd->tmp_out = dup(STDOUT_FILENO);
			if (fd->tmp_out == -1)
			{
				throw_error("dup");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
		switch_fd(ms, fd, parse->infile, parse->outfile);
		ms->exit_status = exec_built_in(ms, parse);
		reset_fds(ms, fd);
		close_all_fds(fd, ms->cl.cmd_count);
		return (1);
	}
	return (0);
}

void	do_exec(t_ms *ms, t_parse *parse)
{
	size_t	i;
	t_parse	*current_parse;

	if (is_only_builtin_cmd(ms, parse, &(ms->fd)))
		return ;
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
			// if (handle_redirection(ms, parse))
			signal(SIGINT, SIG_DFL);
			find_cmd(ms, current_parse);
			// printf("cmd: %s\n", ms->cl.path);
			// printf("infile: %s\n", parse->infile);
			set_pipe_fds(ms, current_parse, &(ms->fd), i);
			close_all_fds(&(ms->fd), ms->cl.cmd_count);
			do_execve(ms, current_parse);
			reset_fds(ms, &(ms->fd));
			exit(EXIT_SUCCESS);
		}
		else
		{
			close_parent_fd(ms, &(ms->fd), i);
			current_parse = current_parse->next;
		}
		i++;
	}
}
