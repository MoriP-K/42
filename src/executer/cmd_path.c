/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoriyam <kmoriyam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:44:49 by kmoriyam          #+#    #+#             */
/*   Updated: 2025/04/21 22:19:39 by kmoriyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_executable_file(char *cmd)
{
	if (!cmd)
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

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

int	check_builtin_cmd(char *cmd)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
			"env", "exit", NULL};
	int					i;
	size_t					len;

	len = ft_strlen(cmd);
	if (!cmd || len == 0)
		return (0);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd, builtins[i], len) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	cmd_not_found(t_ms *ms, char *cmd)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_ms(ms);
	// ms->exit_status = 127;
	exit(127);
}

void	find_cmd(t_ms *ms, t_parse *parse)
{
	if (!parse->cmd)
		return ;
	if (ms->cl->cmd_count > 0 && check_builtin_cmd(parse->cmd))
		return ;
	else if (ft_strchr(parse->cmd, '/'))
	{
		if (is_executable_file(parse->cmd))
			ms->cl->path = parse->cmd;
		else
		{
			throw_error(parse->cmd);
			free_ms(ms);
		}
		return ;
	}
	else
	{
		ms->cl->path = find_cmd_path(parse->cmd, ms->env, ms);
		if (!ms->cl->path)
		{
			cmd_not_found(ms, parse->cmd);
			throw_error(parse->cmd);
			free_ms(ms);
		}
		return ;
	}
}
