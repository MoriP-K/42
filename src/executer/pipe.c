/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:18:41 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/28 23:38:57 by kmoriyam         ###   ########.fr       */
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

void	switch_fd(t_ms *ms, t_fd *fd, t_parse *parse, t_token *token)
{
	t_token	*tmp_token;

	tmp_token = token;
	while (tmp_token)
	{
		if (tmp_token->kinds == TK_IN_REDIRECT && tmp_token->next)
		{
			if (fd->infile >= 0)
				close(fd->infile);
			fd->infile = open(tmp_token->next->word, O_RDONLY);
			if (fd->infile < 0)
			{
				throw_error("open infile");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd->infile, STDIN_FILENO) == -1)
			{
				throw_error("dup2 infile");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
		else if (tmp_token->kinds == TK_HEREDOC)
		{
			if (fd->here_doc >= 0)
				close(fd->here_doc);
			fd->here_doc = open(parse->heredoc_file, O_RDONLY);
			if (fd->here_doc < 0)
			{
				throw_error("s open here_doc");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd->here_doc, STDIN_FILENO) == -1)
			{
				throw_error("dup2 here_doc");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
		else if (tmp_token->kinds == TK_OUT_REDIRECT || tmp_token->kinds == TK_APPEND)
		{
			if (fd->outfile >= 0)
				close(fd->outfile);
			if (parse->append)
				fd->outfile = open(tmp_token->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				fd->outfile = open(tmp_token->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd->outfile < 0)
			{
				throw_error("open outfile error");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
			if (dup2(fd->outfile, STDOUT_FILENO) == -1)
			{
				throw_error("dup2 outfile");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
		tmp_token = tmp_token->next;
	}
}

void	set_pipe_fds(t_ms *ms, t_parse *parse, t_fd *fd, size_t index)
{
	if (index == 0)
	{
		if (ms->cl->cmd_count > 1)
		{
			if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
			{
				throw_error("dup2_a");
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
	}
	else if (index == ms->cl->cmd_count - 1)
	{
		if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
		{
			throw_error("dup2_b");
			free_ms(ms);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (dup2(fd->pipe[index - 1][0], STDIN_FILENO) == -1)
		{
			throw_error("dup2_aa");
			free_ms(ms);
			exit(EXIT_FAILURE);
		}
		fd->tmp_in = fd->pipe[index - 1][0];
		if (dup2(fd->pipe[index][1], STDOUT_FILENO) == -1)
		{
			throw_error("dup2_bb");
			free_ms(ms);
			exit(EXIT_FAILURE);
		}
	}
	if (parse->infile || parse->outfile || parse->delimiter)
		switch_fd(ms, parse->fd, parse, parse->token);
	close_fds(ms, ms->fd, parse, index);
}

void	reset_fds(t_ms *ms, t_fd *fd)
{
	if (fd->tmp_in != -1)
	{
		if (dup2(fd->tmp_in, STDIN_FILENO) == -1)
		{
			throw_error("dup2r infile");
			free_ms(ms);
		}
		close(fd->tmp_in);
		fd->tmp_in = -1;
	}
	if (fd->tmp_out != -1)
	{
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
	if (ms->cl->cmd_count == 1 && check_builtin_cmd(parse->cmd))
	{
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
		switch_fd(ms, fd, parse, parse->token);
		ms->exit_status = exec_built_in(ms, parse);
		reset_fds(ms, fd);
		close_all_fds(fd, parse, ms->cl->cmd_count);
		return (1);
	}
	return (0);
}

void	exec_heredoc(t_ms *ms, t_parse *parse)
{
	char	*line;
	char	*file_num;
	t_parse	*tmp_parse;
	t_token	*tmp_token;
	int		index;

	tmp_parse = parse;
	index = 1;
	while (tmp_parse)
	{
		if (tmp_parse->delimiter)
		{
			file_num = ft_itoa(index++);
			tmp_parse->heredoc_file = ms_strjoin("/tmp/heredoc_", file_num, ms);
			free(file_num);
			tmp_parse->fd->here_doc = open(tmp_parse->heredoc_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp_parse->fd->here_doc < 0)
			{
				throw_error("open heredoc");
				unlink(tmp_parse->heredoc_file);
				free_ms(ms);
				exit(EXIT_FAILURE);
			}
		}
		tmp_parse = tmp_parse->next;
	}
	tmp_parse = parse;
	while (tmp_parse && tmp_parse->delimiter)
	{
		tmp_token = tmp_parse->token;
		while (tmp_token)
		{
			if (tmp_token->kinds == TK_HEREDOC && tmp_token->next)
			{
				tmp_token = tmp_token->next;
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, tmp_token->word) == 0)
					{
						close(tmp_parse->fd->here_doc);
						free(line);
						break ;
					}
					write(tmp_parse->fd->here_doc, line, ft_strlen(line));
					write(tmp_parse->fd->here_doc, "\n", 1);
					free(line);
				}
			}
			tmp_token = tmp_token->next;
		}
		close(tmp_parse->fd->here_doc);
		tmp_parse->fd->here_doc = -1;
		tmp_parse = tmp_parse->next;
	}
	tmp_parse = parse;
	while (tmp_parse)
	{
		if(tmp_parse->delimiter && tmp_parse->fd->here_doc >= 0)
		{
			close(tmp_parse->fd->here_doc);
			tmp_parse->fd->here_doc = -1;
		}
		tmp_parse = tmp_parse->next;
	}
}

void	prepare_heredoc(t_ms *ms, t_fd *fd, t_parse *parse, char *delimiter)
{
	t_parse	*tmp_parse;
	t_token	*token;

	if (!delimiter || !parse->token)
		return ;
	tmp_parse = parse;
	tmp_parse->fd = fd;
	if (tmp_parse->token)
	{
		token = tmp_parse->token;
		while (token)
		{
			if (token->kinds == TK_HEREDOC && token->next)
			{
				fd->tmp_in = dup(STDIN_FILENO);
				fd->tmp_out = dup(STDOUT_FILENO);
				if (fd->tmp_in < 0 || fd->tmp_out < 0)
				{
					throw_error("dup hd error");
					free_ms(ms);
					exit(EXIT_FAILURE);
				}
				token = token->next;
				exec_heredoc(ms, tmp_parse);
				reset_fds(ms, ms->fd);
				break ;
			}
			else
				token = token->next;
		}
	}
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
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			find_cmd(ms, current_parse);
			set_pipe_fds(ms, current_parse, ms->fd, i);
			do_execve(ms, current_parse);
			close_all_fds(ms->fd, current_parse, ms->cl->cmd_count);
			// reset_fds(ms, ms->fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close_parent_fd(ms, ms->fd, i);
			current_parse = current_parse->next;
			i++;
		}
	}
	return (1);
}
