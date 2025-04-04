/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:40:33 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/30 21:39:36 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fds(t_ms *ms, t_fd *fd, size_t index)
{
	if (ms->cl.cmd_count > 1)
	{
		if (index == 0)
		{
			close(fd->pipe[index][1]);
		}
		else if (index == ms->cl.cmd_count - 1)
		{
			close(fd->pipe[index - 1][0]);
		}
		else
		{	
			close(fd->pipe[index][0]);
			close(fd->pipe[index - 1][1]);
		}
	}
}

void	close_all_fds(t_fd *fd, int cmd_count)
{
	int	i;

	if (fd->infile >= 0)
		close(fd->infile);
	if (fd->outfile >= 0)
		close(fd->outfile);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (fd->pipe[i][0] >= 0)
			close(fd->pipe[i][0]);
		if (fd->pipe[i][1] >= 0)
			close(fd->pipe[i][1]);
		i++;
	}
}

void	close_parent_fd(t_ms *ms, t_fd *fd, size_t index)
{
	if (!fd->pipe)
		return ;
	if (index < ms->cl.cmd_count - 1 && fd->pipe[index])
		close(fd->pipe[index][1]);
	if (index > 0 && index <= ms->cl.cmd_count - 1 && fd->pipe[index - 1])
		close(fd->pipe[index - 1][0]);
}
