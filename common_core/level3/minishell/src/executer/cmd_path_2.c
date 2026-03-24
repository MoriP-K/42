/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:01:34 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/29 20:07:19 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path_from_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, "PATH", 4) == 0)
			return (tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*join_cmd_and_path(char *cmd, char **split_arr, t_ms *ms)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (split_arr[i])
	{
		path_cmd = ms_strjoin(split_arr[i], cmd, ms);
		if (access(path_cmd, X_OK) == 0)
		{
			free_array(split_arr);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free_array(split_arr);
	return (NULL);
}

char	**add_slash(char **split_arr, t_ms *ms)
{
	int		i;
	char	**added_slash_arr;
	int		arr_len;

	arr_len = ft_arrlen(split_arr);
	added_slash_arr = (char **)ms_malloc(sizeof(char *) * (arr_len + 1), ms);
	if (!added_slash_arr)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		added_slash_arr[i] = ms_strjoin(split_arr[i], "/", ms);
		if (!added_slash_arr[i])
		{
			free_array(added_slash_arr);
			free_array(split_arr);
			return (NULL);
		}
		i++;
	}
	added_slash_arr[i] = NULL;
	free_array(split_arr);
	return (added_slash_arr);
}

char	*find_cmd_path(char *cmd, t_env *env, t_ms *ms)
{
	char	*path;
	char	**split_arr;

	if (ft_strlen(cmd) == 0)
		return (NULL);
	path = find_path_from_env(env);
	if (!path)
		return (NULL);
	split_arr = ft_split(path, ':');
	if (!split_arr)
		return (NULL);
	split_arr = add_slash(split_arr, ms);
	if (!split_arr)
		return (NULL);
	return (join_cmd_and_path(cmd, split_arr, ms));
}
