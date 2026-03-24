/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:28:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/01 21:29:31 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_heredoc(t_ms *ms, t_parse *parse)
{
	t_parse	*tmp_parse;

	make_heredoc_file(parse, ms);
	write_to_heredoc_file(parse);
	if (g_sigint_received == 1)
		return ;
	tmp_parse = parse;
	while (tmp_parse)
	{
		if (tmp_parse->delimiter && tmp_parse->fd->here_doc >= 0)
		{
			close(tmp_parse->fd->here_doc);
			tmp_parse->fd->here_doc = -1;
		}
		tmp_parse = tmp_parse->next;
	}
}

int	is_sigint_received(void)
{
	if (g_sigint_received == 1)
	{
		g_sigint_received = 0;
		return (1);
	}
	return (0);
}

void	set_fd_for_heredoc(t_fd *fd, t_parse *tmp_parse,
	t_token *token, t_ms *ms)
{
	fd->tmp_in = ms_dup(STDIN_FILENO, ms);
	fd->tmp_out = ms_dup(STDOUT_FILENO, ms);
	token = token->next;
	exec_heredoc(ms, tmp_parse);
	reset_fds(ms, ms->fd);
}

void	prepare_heredoc(t_ms *ms, t_fd *fd, t_parse *parse)
{
	t_parse	*tmp_parse;
	t_token	*token;

	set_heredoc_sigint();
	if (!parse->token)
		return ;
	tmp_parse = parse;
	while (tmp_parse && tmp_parse->token)
	{
		token = tmp_parse->token;
		while (token)
		{
			if (is_sigint_received())
				return ;
			if (token->kinds == TK_HEREDOC && token->next)
			{
				set_fd_for_heredoc(fd, tmp_parse, token, ms);
				break ;
			}
			else
				token = token->next;
		}
		tmp_parse = tmp_parse->next;
	}
}
