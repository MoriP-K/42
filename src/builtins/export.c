/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:18:19 by masa              #+#    #+#             */
/*   Updated: 2025/04/18 14:03:41 by motomo           ###   ########.fr       */
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

void	if_export_sort(t_ms *ms, int i)
{
	if (i != 1)
	{
		free_env(&ms->env);
		init_env(&ms->env, ms->envp, ms);
	}
	else
		export_sort(ms);
}

void	set_new_envp(t_ms *ms, t_parse *parse, int i)
{
	int		count;
	char	**new_envp;

	count = 0;
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

int	export_handler(t_ms *ms, t_parse *parse, int *return_value, int *i)
{
	int		index;
	char	*key;

	index = 0;
	if (export_has_wrong_char(parse->args[*i]))
	{
		*return_value = export_error(parse->args[*i]);
		(*i)++;
		return (0);
	}
	if (!split_key_value(parse->args[*i], &key, ms))
	{
		(*i)++;
		return (0);
	}
	index = find_env_index(ms->envp, key);
	if (index == -1)
		set_new_envp(ms, parse, *i);
	else
	{
		free(ms->envp[index]);
		ms->envp[index] = ms_strdup(parse->args[*i], ms);
	}
	free(key);
	return (1);
}

int	builtin_export(t_ms *ms, t_parse *parse)
{
	int		i;
	int		return_value;

	return_value = 0;
	i = 1;
	while (parse->args[i])
	{
		if (!export_handler(ms, parse, &return_value, &i))
			continue ;
		i++;
	}
	if_export_sort(ms, i);
	return (return_value);
}
