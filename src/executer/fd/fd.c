/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:33:05 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:30:47 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	switch_to_out_redir(t_ms *ms, t_fd *fd,
	t_parse *parse, t_token *tmp_token)
{
	if (parse->append)
		fd->outfile = ms_open_mode(tmp_token->next->word,
				O_WRONLY | O_CREAT | O_APPEND, 0644, ms);
	else
		fd->outfile = ms_open_mode(tmp_token->next->word,
				O_WRONLY | O_CREAT | O_TRUNC, 0644, ms);
}

void	switch_redirect(t_ms *ms, t_fd *fd, t_parse *parse, t_token *tmp_token)
{
	if (tmp_token->kinds == TK_IN_REDIRECT && tmp_token->next)
	{
		if (fd->infile >= 0)
			close(fd->infile);
		fd->infile = ms_open(tmp_token->next->word, O_RDONLY, ms);
		ms_dup2(fd->infile, STDIN_FILENO, ms);
	}
	else if (tmp_token->kinds == TK_HEREDOC)
	{
		if (fd->here_doc >= 0)
			close(fd->here_doc);
		fd->here_doc = ms_open(parse->heredoc_file, O_RDONLY, ms);
		ms_dup2(fd->here_doc, STDIN_FILENO, ms);
	}
	else if (tmp_token->kinds == TK_OUT_REDIRECT
		|| tmp_token->kinds == TK_APPEND)
	{
		if (fd->outfile >= 0)
			close(fd->outfile);
		switch_to_out_redir(ms, fd, parse, tmp_token);
		ms_dup2(fd->outfile, STDOUT_FILENO, ms);
	}
}

void	switch_fd(t_ms *ms, t_fd *fd, t_parse *parse, t_token *token)
{
	t_token	*tmp_token;

	tmp_token = token;
	while (tmp_token)
	{
		switch_redirect(ms, fd, parse, tmp_token);
		tmp_token = tmp_token->next;
	}
}

void	set_pipe_fds(t_ms *ms, t_parse *parse, t_fd *fd, size_t index)
{
	if (index == 0)
	{
		if (ms->cl->cmd_count > 1)
			ms_dup2(fd->pipe[index][1], STDOUT_FILENO, ms);
	}
	else if (index == ms->cl->cmd_count - 1)
		ms_dup2(fd->pipe[index - 1][0], STDIN_FILENO, ms);
	else
	{
		ms_dup2(fd->pipe[index - 1][0], STDIN_FILENO, ms);
		fd->tmp_in = fd->pipe[index - 1][0];
		ms_dup2(fd->pipe[index][1], STDOUT_FILENO, ms);
	}
	if (parse->infile || parse->outfile || parse->delimiter)
		switch_fd(ms, parse->fd, parse, parse->token);
	close_fds(ms, ms->fd, parse, index);
}

void	reset_fds(t_ms *ms, t_fd *fd)
{
	if (fd->tmp_in != -1)
	{
		ms_dup2(fd->tmp_in, STDIN_FILENO, ms);
		close(fd->tmp_in);
		fd->tmp_in = -1;
	}
	if (fd->tmp_out != -1)
	{
		ms_dup2(fd->tmp_out, STDOUT_FILENO, ms);
		close(fd->tmp_out);
		fd->tmp_out = -1;
	}
}
