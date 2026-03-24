/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:40:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:22:09 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	close_fds(t_ms *ms, t_fd *fd, t_parse *parse, size_t index)
{
	if (parse->fd->here_doc != -1)
		close(parse->fd->here_doc);
	if (ms->cl->cmd_count > 1)
	{
		if (index == 0)
			close(fd->pipe[index][1]);
		else if (index == ms->cl->cmd_count - 1)
			close(fd->pipe[index - 1][0]);
		else
		{
			close(fd->pipe[index][0]);
			close(fd->pipe[index - 1][1]);
		}
	}
}

void	close_parse_fds(t_parse *parse)
{
	t_parse	*tmp_parse;

	tmp_parse = parse;
	while (tmp_parse)
	{
		if (tmp_parse->fd)
		{
			if (tmp_parse->fd->infile != -1)
			{
				close(tmp_parse->fd->infile);
				tmp_parse->fd->infile = -1;
			}
			if (tmp_parse->fd->outfile != -1)
			{
				close(tmp_parse->fd->outfile);
				tmp_parse->fd->outfile = -1;
			}
			if (tmp_parse->fd->here_doc != -1)
			{
				close(tmp_parse->fd->here_doc);
				tmp_parse->fd->here_doc = -1;
			}
		}
		tmp_parse = tmp_parse->next;
	}
}

void	close_all_fds(t_fd *fd, t_parse *parse, int cmd_count)
{
	int	i;

	i = 0;
	while (cmd_count > 1 && i < cmd_count - 1)
	{
		if (fd->pipe[i][0] != -1)
			close(fd->pipe[i][0]);
		if (fd->pipe[i][1] != -1)
			close(fd->pipe[i][1]);
		i++;
	}
	close_parse_fds(parse);
}

void	close_parent_fd(t_ms *ms, t_fd *fd, size_t index)
{
	if (index < ms->cl->cmd_count - 1)
	{
		close(fd->pipe[index][1]);
		fd->pipe[index][1] = -1;
	}
	if (index > 0)
	{
		close(fd->pipe[index - 1][0]);
		fd->pipe[index - 1][0] = -1;
	}
}
