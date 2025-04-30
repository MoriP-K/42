/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:08 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/05/01 00:14:09 by kmoriyam         ###   ########.fr       */
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
	if (ms->token)
		free_tokens(ms->token);
	if (ms->proc)
		free_proc(ms->proc);
	if (ms->fd)
		free_fd(ms->fd, ms->cl);
	if (ms->cl)
		free_cl(ms->cl);
}

void	free_proc(t_proc *proc)
{
	if (proc->id)
		free(proc->id);
	free(proc);
}

void	free_parser2(t_parse *parse)
{
	if (parse->cmd)
		free(parse->cmd);
	if (parse->infile)
		free(parse->infile);
	if (parse->outfile)
		free(parse->outfile);
	if (parse->heredoc_file)
	{
		unlink(parse->heredoc_file);
		free(parse->heredoc_file);
	}
	if (parse->delimiter)
		free(parse->delimiter);
	if (parse->fd)
		free(parse->fd);
}

void	free_parser(t_parse *parse)
{
	t_parse	*tmp;
	int		i;

	while (parse)
	{
		tmp = parse->next;
		i = 0;
		if (parse->token)
			free_tokens(parse->token);
		if (parse->args)
		{
			while (parse->args[i])
				free(parse->args[i++]);
			free(parse->args);
		}
		free_parser2(parse);
		free(parse);
		parse = tmp;
	}
	free(parse);
}
