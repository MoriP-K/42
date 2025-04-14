/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:19 by masa              #+#    #+#             */
/*   Updated: 2025/04/14 14:48:07 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_env_index(char **envp, char *key)
{
	size_t	key_len;
	int		i;

	key_len = ft_strlen(key);
	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	split_key_value(char *arg, char **out_key, char **out_value)
{
	char	*eq;
	int		key_len;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		out_key = NULL;
		out_value = NULL;
	}
	key_len = eq - arg;
	if (key_len == 0)
		return (0);
	*out_key = ft_strndup(arg, arg + key_len);
	*out_value = ft_strdup(eq + 1);
	return (1);
}

void	free_old_envp(char **envp)
{
	int	i;
	int	count;

	i = 0;
	if (!envp)
		return;
	count = 0;
	while (envp[i++])
		count++;
	i = 0;
	while (envp[i] && i < count)
		free(envp[i++]);
	free(envp);
}

int	error(char *arg)
{
	write(2, "export: `", 8);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	return (1);
}

int	builtin_export(t_ms *ms, t_parse *parse)
{
	int		i;
	int		return_value;
	int 	count;
	int		index;
	char	*key;
	char	*value;
	char	**new_envp;

	index = 0;
	count = 0;
	i = 1;
	while (parse->args[i])
	{
		if (!split_key_value(parse->args[i], &key, &value))
		{
			return_value = error(parse->args[i]);
			i++;
			continue;
		}
		index = find_env_index(ms->envp, key);
		if (index == -1)
		{
			while (ms->envp && ms->envp[count])
				count++;
			new_envp = (char **)malloc(sizeof(char *) * (count + 2));
			count = 0;
			while (ms->envp && ms->envp[count])
			{
				new_envp[count] = ft_strdup(ms->envp[count]);
				count++;
			}
			free_old_envp(ms->envp);
			new_envp[count] = ft_strdup(parse->args[i]);
			new_envp[count + 1] = NULL;
			ms->envp = new_envp;
		}
		else
		{
			free(ms->envp[index]);
			ms->envp[index] = ft_strdup(parse->args[i]);
		}
		free(key);
		free(value);
		i++;
	}
	if (i != 1)
	{
		free_env(&ms->env);
		init_env(&ms->env, ms->envp);
	}
	return (return_value);
}