/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:19 by masa              #+#    #+#             */
/*   Updated: 2025/04/17 21:14:58 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	split_key_value(char *arg, char **out_key, t_ms *ms)
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
	*out_key = ms_strndup(arg, arg + key_len, ms);
	return (1);
}



int	builtin_export(t_ms *ms, t_parse *parse)
{
	int		i;
	int		return_value;
	int		count;
	int		index;
	char	*key;
	char	**new_envp;

	index = 0;
	count = 0;
	return_value = 0;
	i = 1;
	while (parse->args[i])
	{
		if (export_has_wrong_char(parse->args[i]))
		{
			return_value = export_error(parse->args[i]);
			i++;
			continue ;
		}
		if (!split_key_value(parse->args[i], &key, ms))
		{
			i++;
			continue ;
		}
		index = find_env_index(ms->envp, key);
		if (index == -1)
		{
			while (ms->envp && ms->envp[count])
				count++;
			new_envp = (char **)ms_malloc(sizeof(char *) * (count + 2), ms);
			count = 0;
			while (ms->envp && ms->envp[count])
			{
				new_envp[count] = ms_strdup(ms->envp[count], ms);
				count++;
			}
			free_old_envp(ms->envp);
			new_envp[count] = ms_strdup(parse->args[i], ms);
			new_envp[count + 1] = NULL;
			ms->envp = new_envp;
		}
		else
		{
			free(ms->envp[index]);
			ms->envp[index] = ms_strdup(parse->args[i], ms);
		}
		free(key);
		i++;
	}
	if (i != 1)
	{
		free_env(&ms->env);
		init_env(&ms->env, ms->envp, ms);
	}
	else
		export_sort(ms);
	return (return_value);
}
