/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:10:02 by motomo            #+#    #+#             */
/*   Updated: 2025/04/17 21:10:54 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_sorted_envs_and_free(t_env *env, char **keys)
{
	t_env	*first_env;
	int		i;

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
	free_array(keys);
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
	char	**keys;
	int		count;
	t_env	*env;
	t_env	*first_env;

	first_env = ms->env;
	env = ms->env;
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	keys = ms_malloc(sizeof(char *) * (count + 1), ms);
	count = 0;
	env = first_env;
	while (env)
	{
		keys[count] = ms_strdup(env->key, ms);
		env = env->next;
		count++;
	}
	keys[count] = NULL;
	sort_keys(keys, count);
	print_sorted_envs_and_free(first_env, keys);
}
