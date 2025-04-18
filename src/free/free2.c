/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:11:48 by motomo            #+#    #+#             */
/*   Updated: 2025/04/18 14:12:29 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
