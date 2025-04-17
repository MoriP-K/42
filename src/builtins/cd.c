/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motomo <motomo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:34:43 by masa              #+#    #+#             */
/*   Updated: 2025/04/17 21:41:21 by motomo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_cd_error(char *path)
{
	char	*error_msg;

	error_msg = strerror(errno);
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

char	*find_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

int	home_not_set(t_ms *ms)
{
	char	*env_value;

	env_value = find_value(ms->env, "HOME");
	if (!env_value)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	else if (chdir(env_value) != 0)
	{
		write_cd_error(env_value);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_ms *ms, t_parse *parse)
{
	if (parse->args == NULL || parse->args[1] == NULL)
	{
		if (home_not_set(ms))
			return (1);
		return (0);
	}
	if (parse->args[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		return (1);
	}
	if (chdir(parse->args[1]) != 0)
	{
		write_cd_error(parse->args[1]);
		return (1);
	}
	else
		env_pwd_changer(ms);
	return (0);
}
