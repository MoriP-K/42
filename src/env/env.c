/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:29:09 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/03/16 16:29:36 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_key(char *env_var)
{
	char	*key;
	char	*tmp;

	tmp = env_var;
	key = ft_substr(tmp, 0, ft_strnchr(tmp, '=') - 1);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_env_value(char *env_var)
{
	char	*value;
	char	*tmp;
	int		pos;

	tmp = ft_strdup(env_var);
	if (!tmp)
		return (NULL);
	pos = ft_strnchr(tmp, '=');
	while (pos)
	{
		tmp++;
		pos--;
	}
	value = ft_substr(tmp, 0, ft_strlen(tmp));
	if (!value)
	{
		free(tmp);
		return (NULL);
	}
	return (value);
}

t_env	*new_env_lst(void)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
	{
		return (NULL);
	}
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

t_env	*last_env_lst(t_env *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	add_env_lst(t_env **node, t_env *new_env)
{
	t_env	*current;

	if (!*node)
		*node = new_env;
	else
	{
		current = last_env_lst(*node);
		current->next = new_env;
	}
}

void	init_env(t_env **env, char *envp[])
{
	int		i;
	t_env	*new_env;

	i = 0;
	*env = NULL;
	while (envp[i])
	{
		new_env = new_env_lst();
		if (!new_env)
		{
			free(new_env);
			// throw_error();
			exit(EXIT_FAILURE);
		}
		new_env->key = get_env_key(envp[i]);
		new_env->value = get_env_value(envp[i]);
		add_env_lst(env, new_env);
		i++;
	}
}
