/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masa <masa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:17:44 by masa              #+#    #+#             */
/*   Updated: 2025/04/10 21:59:52 by masa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (0);
	return (1);
}

int	find_key_index(char *key, t_env	*env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (string_compare(env->key, key))
			return(count);
		count++;
		env = env->next;
	}
	return (-1);
}

void	builtin_unset(t_ms *ms, t_parse *parse)
{
	int	index;
	int	i;

	i = 1;
	while (parse->args[i])
	{
		index = find_key_index(parse->args[i], ms->env);
		if (index == -1)
		{
			i++;
			continue;
		}
		free(ms->envp[index]);
		while (ms->envp[index + 1])
		{
			ms->envp[index] = ms->envp[index + 1];
			index++;
		}
		ms->envp[index] = NULL;
		free_env(&ms->env);
		init_env(&ms->env, ms->envp);
		i++;
	}
}
