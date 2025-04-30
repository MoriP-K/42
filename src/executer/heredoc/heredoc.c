/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:28:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/30 23:09:09 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	make_heredoc_file(t_parse *parse, t_ms *ms)
{
	t_parse	*tmp_parse;
	char	*file_num;
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
			tmp_parse->fd->here_doc = ms_open_mode(tmp_parse->heredoc_file, \
				O_WRONLY | O_CREAT | O_TRUNC, 0644, ms);
		}
		tmp_parse = tmp_parse->next;
	}
}

void	exec_readline(t_parse *tmp_parse, t_token *tmp_token)
{
	char	*line;

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

void	write_to_heredoc_file(t_parse *parse)
{
	t_parse	*tmp_parse;
	t_token	*tmp_token;

	tmp_parse = parse;
	while (tmp_parse && tmp_parse->delimiter)
	{
		tmp_token = tmp_parse->token;
		while (tmp_token)
		{
			if (tmp_token->kinds == TK_HEREDOC && tmp_token->next)
			{
				tmp_token = tmp_token->next;
				exec_readline(tmp_parse, tmp_token);
			}
			tmp_token = tmp_token->next;
		}
		close(tmp_parse->fd->here_doc);
		tmp_parse->fd->here_doc = -1;
		tmp_parse = tmp_parse->next;
	}
}

void	exec_heredoc(t_ms *ms, t_parse *parse)
{
	t_parse	*tmp_parse;

	make_heredoc_file(parse, ms);
	write_to_heredoc_file(parse);
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

void	prepare_heredoc(t_ms *ms, t_fd *fd, t_parse *parse, char *delimiter)
{
	t_parse	*tmp_parse;
	t_token	*token;

	if (!delimiter || !parse->token)
		return ;
	tmp_parse = parse;
	if (tmp_parse->token)
	{
		token = tmp_parse->token;
		while (token)
		{
			if (token->kinds == TK_HEREDOC && token->next)
			{
				fd->tmp_in = ms_dup(STDIN_FILENO, ms);
				fd->tmp_out = ms_dup(STDOUT_FILENO, ms);
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
