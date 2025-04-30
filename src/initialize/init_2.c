/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:57:45 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 19:58:14 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cl(t_cl **cl, t_parse *parse, t_ms *ms)
{
	t_parse	*tmp;
	int		count;

	*cl = (t_cl *)ms_malloc(sizeof(t_cl), ms);
	tmp = parse;
	count = 0;
	while (tmp)
	{
		if (tmp->cmd || tmp->delimiter)
			count++;
		tmp = tmp->next;
	}
	(*cl)->cmd_count = count;
	(*cl)->path = NULL;
}

void	init_proc(t_proc **proc, t_cl *cl, t_ms *ms)
{
	size_t	i;

	*proc = (t_proc *)ms_malloc(sizeof(t_proc), ms);
	(*proc)->id = (pid_t *)ms_malloc(sizeof(pid_t) * cl->cmd_count, ms);
	i = 0;
	while (i < cl->cmd_count)
		(*proc)->id[i++] = -1;
	(*proc)->status = 0;
}

void	init_fd(t_fd **fd, t_cl *cl, t_ms *ms)
{
	size_t	i;

	*fd = (t_fd *)ms_malloc(sizeof(t_fd), ms);
	(*fd)->pipe = ms_malloc(sizeof(int *) * cl->cmd_count, ms);
	(*fd)->infile = -1;
	(*fd)->outfile = -1;
	(*fd)->tmp_in = -1;
	(*fd)->tmp_out = -1;
	(*fd)->here_doc = -1;
	i = 0;
	while (i < cl->cmd_count)
	{
		(*fd)->pipe[i] = ms_malloc(sizeof(int) * 2, ms);
		(*fd)->pipe[i][0] = -1;
		(*fd)->pipe[i][1] = -1;
		i++;
	}
}

void	init_exec(t_ms *ms, t_parse *parse)
{
	init_cl(&(ms->cl), parse, ms);
	init_proc(&(ms->proc), ms->cl, ms);
	init_fd(&(ms->fd), ms->cl, ms);
}
