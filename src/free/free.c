/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:08 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/21 21:28:32 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_ms *ms)
{
	if (!ms)
		return ;
	free_ms(ms);
	if (ms->envp)
		free_old_envp(ms->envp);
	if (ms->env)
		free_env(&ms->env);
}

void	free_ms(t_ms *ms)
{
	if (ms->parse)
		free_parser(ms->parse);
	if (ms->fd->pipe)
		free_fd(ms->fd, ms->cl);
	if (ms->proc->id)
		free_proc(ms->proc);
}

void	free_proc(t_proc *proc)
{
	if (proc->id)
		free(proc->id);
}

void	free_parser(t_parse *parse)
{
	t_parse	*tmp;
	int		i;

	while (parse)
	{
		tmp = parse->next;
		i = 0;
		if (parse->cmd)
			free(parse->cmd);
		if (parse->args)
		{
			while (parse->args[i])
				free(parse->args[i++]);
			free(parse->args);
		}
		if (parse->infile)
			free(parse->infile);
		if (parse->outfile)
			free(parse->outfile);
		free(parse);
		parse = tmp;
	}
	free(parse);
}
