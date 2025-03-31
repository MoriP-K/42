/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:22:08 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/31 21:06:05 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ms(t_ms *ms)
{
	free_parser(ms->parse);
	free_env(&(ms->env));
	free_fd(&(ms->fd), &(ms->cl));
	free_proc(&(ms->proc));
	return ;
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
	// free(parse);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_fd(t_fd *fd, t_cl *cl)
{
	size_t	i;

	i = 0;
	while (i < cl->cmd_count)
	{
		if (fd->pipe[i])
			free(fd->pipe[i]);
		i++;
	}
	free(fd->pipe);
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*tmp;

	if (!*env)
		return ;
	current = *env;
	while (current)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
}