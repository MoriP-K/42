/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:19 by masa              #+#    #+#             */
/*   Updated: 2025/04/14 18:28:01 by motomo           ###   ########.fr       */
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

int	split_key_value(char *arg, char **out_key)
{
	char	*eq;
	int		key_len;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*out_key = NULL;
		return (0);
	}
	key_len = eq - arg;
	if (key_len == 0)
		return (0);
	*out_key = ft_strndup(arg, arg + key_len);
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

void	free_string(char **str)
{
	int	i;
	
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	print_sorted_envs_and_free(t_env *env, char **keys)
{
	t_env	*first_env;
	int			i;
	
	first_env = env;
	i = 0;
	while (keys[i])
	{
		env = first_env;
		while (env)
		{
			if (!ft_strcmp(env->key, keys[i]) && ft_strcmp(env->key, "_"))
			{
				write(1, "declare -x ", 11);
				write(1, env->key, ft_strlen(env->key));
				write(1, "=\"", 2);
				write(1, env->value, ft_strlen(env->value));
				write(1, "\"\n", 2);
				break ;
			}
			env = env->next;
		}
		i++;
	}
	free_string(keys);
}

void	sort_keys(char **keys, int count)
{
	int		i;
	int		j;
	char	*temp;
	
	while (count > 0)
	{
		i = 0;
		while (keys[i + 1])
		{
			j = 0;
			while (keys[i][j] && keys[i + 1][j] && keys[i][j] == keys[i + 1][j])
				j++;
			if (keys[i][j] > keys[i + 1][j])
			{
				temp = keys[i];
				keys[i] = keys[i + 1];
				keys[i + 1] = temp;
			}
			i++;
		}
		count--;
	}
}

void	export_sort(t_ms *ms)
{
	char		**keys;
	int			count;
	t_env		*env;
	t_env	*first_env;

	first_env = ms->env;
	env = ms->env;
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	keys = malloc(sizeof(char *) * (count + 1));
	count = 0;
	env = first_env;
	while (env)
	{
		keys[count] = ft_strdup(env->key);
		env = env->next;
		count++;
	}
	keys[count] = NULL;
	sort_keys(keys, count);
	print_sorted_envs_and_free(first_env, keys);
}

int	builtin_export(t_ms *ms, t_parse *parse)
{
	int		i;
	int		return_value;
	int 	count;
	int		index;
	char	*key;
	char	**new_envp;

	index = 0;
	count = 0;
	i = 1;
	while (parse->args[i])
	{
		if (!split_key_value(parse->args[i], &key))
		{
			if (key != NULL)
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
		i++;
	}
	if (i != 1)
	{
		free_env(&ms->env);
		init_env(&ms->env, ms->envp);
	}
	else
		export_sort(ms);
	return (return_value);
}
